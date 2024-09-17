#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <tuple>

#include "matrix.h"

using namespace std;

// static parameter
// float lengths[] = {5,10,50,100,150,200,250,300,350,400};
float lengths[] = {100,200,300,400,500,600,700,800};
int32_t num_lengths = 8;

struct errors {
  int32_t first_frame;
  float   r_err;
  float   t_err;
  float   len;
  float   speed;
  errors (int32_t first_frame,float r_err,float t_err,float len,float speed) :
    first_frame(first_frame),r_err(r_err),t_err(t_err),len(len),speed(speed) {}
};

vector<Matrix> loadPoses(string file_name) {
  vector<Matrix> poses;
  FILE *fp = fopen(file_name.c_str(),"r");
  if (!fp)
    return poses;
  while (!feof(fp)) {
    Matrix P = Matrix::eye(4);
    if (fscanf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
                   &P.val[0][0], &P.val[0][1], &P.val[0][2], &P.val[0][3],
                   &P.val[1][0], &P.val[1][1], &P.val[1][2], &P.val[1][3],
                   &P.val[2][0], &P.val[2][1], &P.val[2][2], &P.val[2][3] )==12) {
      poses.push_back(P);
    }
  }
  fclose(fp);
  return poses;
}

vector<float> trajectoryDistances (vector<Matrix> &poses) {
  vector<float> dist;
  dist.push_back(0);
  for (int32_t i=1; i<poses.size(); i++) {
    Matrix P1 = poses[i-1];
    Matrix P2 = poses[i];
    float dx = P1.val[0][3]-P2.val[0][3];
    float dy = P1.val[1][3]-P2.val[1][3];
    float dz = P1.val[2][3]-P2.val[2][3];
    dist.push_back(dist[i-1]+sqrt(dx*dx+dy*dy+dz*dz));
  }
  return dist;
}

int32_t lastFrameFromSegmentLength(vector<float> &dist,int32_t first_frame,float len) {
  for (int32_t i=first_frame; i<dist.size(); i++)
    if (dist[i]>dist[first_frame]+len)
      return i;
  return -1;
}

inline float rotationError(Matrix &pose_error) {
  float a = pose_error.val[0][0];
  float b = pose_error.val[1][1];
  float c = pose_error.val[2][2];
  float d = 0.5*(a+b+c-1.0);
  return acos(max(min(d,1.0f),-1.0f));
}

inline float translationError(Matrix &pose_error) {
  float dx = pose_error.val[0][3];
  float dy = pose_error.val[1][3];
  float dz = pose_error.val[2][3];
  return sqrt(dx*dx+dy*dy+dz*dz);
}

vector<errors> calcSequenceErrors (vector<Matrix> &poses_gt,vector<Matrix> &poses_result) {

  // error vector
  vector<errors> err;

  // parameters
  int32_t step_size = 10; // every second
  
  // pre-compute distances (from ground truth as reference)
  vector<float> dist = trajectoryDistances(poses_gt);
 
  // for all start positions do
  for (int32_t first_frame=0; first_frame<poses_gt.size(); first_frame+=step_size) {
  
    // for all segment lengths do
    for (int32_t i=0; i<num_lengths; i++) {
    
      // current length
      float len = lengths[i];
      
      // compute last frame
      int32_t last_frame = lastFrameFromSegmentLength(dist,first_frame,len);
      
      // continue, if sequence not long enough
      if (last_frame==-1)
        continue;

      // compute rotational and translational errors
      Matrix pose_delta_gt     = Matrix::inv(poses_gt[first_frame])*poses_gt[last_frame];
      Matrix pose_delta_result = Matrix::inv(poses_result[first_frame])*poses_result[last_frame];
      Matrix pose_error        = Matrix::inv(pose_delta_result)*pose_delta_gt;
      float r_err = rotationError(pose_error);
      float t_err = translationError(pose_error);
      
      // compute speed
      float num_frames = (float)(last_frame-first_frame+1);
      float speed = len/(0.1*num_frames);
      
      // write to file
      err.push_back(errors(first_frame,r_err/len,t_err/len,len,speed));
    }
  }

  // return error vector
  return err;
}

std::tuple<float, float> calcStats (vector<errors> err) {

  float t_err = 0;
  float r_err = 0;

  // for all errors do => compute sum of t_err, r_err
  for (vector<errors>::iterator it=err.begin(); it!=err.end(); it++) {
    t_err += it->t_err;
    r_err += it->r_err;
  }

  // save errors
  float num = err.size();
  return make_tuple(t_err/num * 100, r_err/num / 3.14 * 180.0);
}

vector<errors> eval (string sequence_id, string result_file, int start, int end) {

  // ground truth and result directories
  string gt_dir         = "data/odometry/poses";
  
  // read ground truth and result poses
  vector<Matrix> poses_gt     = loadPoses(gt_dir + "/" + sequence_id + ".txt");
  vector<Matrix> poses_result = loadPoses(result_file);
  
  if (end == -1) {
    end = poses_gt.size(); 
  }

  poses_gt.erase(poses_gt.begin() + end, poses_gt.end());
  poses_gt.erase(poses_gt.begin(), poses_gt.begin() + start);
  
  // check for errors
  if (poses_result.size() != poses_gt.size()) {
    cerr << "#gt poses (" << poses_gt.size() << ") != #result poses (" << poses_result.size() << ")" << endl;
  }

  // compute sequence errors
  vector<errors> seq_err = calcSequenceErrors(poses_gt,poses_result);

  return seq_err;
	// return calcStats(seq_err);
}

int32_t main (int32_t argc,char *argv[]) {

  if (argc < 4 || argc > 6) {
      cerr << "Usage: ./eval_odometry dataset sequence_id result_poses.txt start_frame (0 default), end_frame (-1, the last, by default)" << endl;
      return 1;
  }

  // read arguments
  string dataset = argv[1];
  string sequence_id = argv[2];
  string result_file = argv[3];

  int start_frame = 0;
  int end_frame = -1;

  if (argc >= 5) {
      start_frame = std::stoi(argv[4]);
  }

  if (argc == 6) {
      end_frame = std::stoi(argv[5]);
  }

  // run evaluation
  vector<errors> seq_err = eval(sequence_id, result_file, start_frame, end_frame);

  // get stats
  tuple<float, float> stats = calcStats(seq_err);
  cout << dataset << ", " << sequence_id << ", " << get<0>(stats) << ", " << get<1>(stats) << endl;
  return 0;
}
