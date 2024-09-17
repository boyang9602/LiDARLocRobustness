## NeRF-LOAM
NeRF-LOAM has many system level dependencies and is a bit hard to build in docker. 
We provide a Dockerfile, a script to build the docker image, and a script to run the evaluation on all LiDAR data corruptions. 
Please check [our cloned repo](https://github.com/boyang9602/NeRF-LOAM) to build and evaluate. 

[raw_results](./raw_results/) contains all the raw output from NeRF-LOAM. Note that NeRF-LOAM also produces the reconstruction of the scene, which are large files. We do not contain them in this git repo. 
[corruption](./raw_results/corruption/) are the raw output on the corrupted data.
[corruption2](./raw_results/corruption2/) are the raw output on a few corrupted data for another trial. They are run on the exact same data with the corresponding corruption under [corruption](./raw_results/corruption/). However, their performance are quite different. 
Under corruption, the folder name indicates the corruption type (it is the clean data if no corruption name).
`frame_poses.txt` is the original output while `calib_poses.txt` is the calibrated poses using KITTI calibration files. 

[eval_results](./eval_results/) contains the evaluation of the estimated poses on corrupted data against the ground truth. We did not run it on the denoised data because it does not produce the same results even for the same intput data. Thus it is impossible to know if it is the denoising making it better or worse. 

[monitor.sh] is a monitor script to detect the failure of NeRF-LOAM processes. NeRF-LOAM requires high GPU memory (at least 24GB) and it may encounter "CUDA out of memory" issue or runtime errors where it outputs "Encouter a bug ...". It will hang and block the further experiments. This scripts detect the error messages from logs and kill the corresponding docker processes. So the run.sh script will schedule the run on the next corrupted data. This script should be registered as a crontab to be executed every 5 or 10 minutes. 

### Steps
1. `./build_docker.sh` (to be done)
2. `./run.sh`

Note that NeRF-LOAM cannot produce the same results during different trials on the same data. So you are unlikely to get exact same results as ours. However, it should be similar in general. 