# Evaluation code

This evaluation code is adapted from [the official evaluation code from KITTI Odometry](https://www.cvlibs.net/datasets/kitti/eval_odometry.php). 

## Compile
```
g++ -o eval_seq eval_seq.cpp matrix.h matrix.cpp
```

## Run
```
Usage: ./eval_seq dataset sequence_id result_poses.txt start_frame (0 default), end_frame (-1, the last, by default)
```
It will compare result_poses.txt with the ground truth of the sequence_id under [data/](./data/). You can only compare a subset of the sequence by specifying the start and end frame ids.