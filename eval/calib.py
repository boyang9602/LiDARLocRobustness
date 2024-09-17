import sys
import numpy as np
def load_LoPose(filename):
    # load Lidar Odometry (SLAM) pose (in camera/body frame)
    with open(filename, 'r') as f:
        data = f.readlines()
        data = [i.split(' ') for i in data]
        data = np.array(data, dtype=np.float32).reshape(-1, 3, 4)
        data_row4 = np.array([0, 0, 0, 1]).reshape(1, 1, 4).repeat(data.shape[0],axis=0)
        data = np.concatenate([data, data_row4], axis=1)
    return data

def load_Kitti_calib(filename):
    CalibRT = np.identity(4)
    with open(filename, 'r') as f:
        data = f.readlines()
        for line in data:
            if line[:2] == 'Tr':
                RTtmp = np.array(line[3:].split()).reshape(3,4)
    CalibRT[:3,:] = RTtmp
    return CalibRT

if __name__ == '__main__':
    poses = load_LoPose(sys.argv[1])
    calib = load_Kitti_calib('calib.txt')
    c_poses = calib @ poses @ np.linalg.inv(calib)
    np.savetxt(sys.argv[2], c_poses[:, :3].reshape(c_poses.shape[0], -1))