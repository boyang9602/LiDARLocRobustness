# Evaluation code

This evaluation code is adapted from [the official evaluation code from KITTI Odometry](https://www.cvlibs.net/datasets/kitti/eval_odometry.php). 

## Compile
```
g++ -o eval_seq eval_seq.cpp matrix.h matrix.cpp
```

## Run
The compiled eval_seq can be used to evaluate a single sequence pose file. 
```
Usage: ./eval_seq dataset sequence_id result_poses.txt start_frame (0 default), end_frame (-1, the last, by default)
```
It will compare result_poses.txt with the ground truth of the sequence_id under [data/](./data/). If you only want to compare a subset of the sequence, you can specify the start and end frame ids.
The output for is `corruption_type, sequence, RPE_{trans}, RPE_{rot}`. 

The shell scripts under this folder could generate the evaluation results for all LiDAR corruption datasets and all sequences for each subject system. They require an arg for the pose files folder. 
