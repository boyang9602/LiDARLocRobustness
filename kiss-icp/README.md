## kiss-icp
kiss-icp is a python project and can be installed through pip. Please refer to [the official git repo](https://github.com/PRBonn/kiss-icp) for the installation (basic installation is enough). We provide [a script](./run.sh) to run the evaluation on all LiDAR data corruptions. 
The script requires 2 args, the first one is the datasets root folder and the second one is the output root folder (it is better to be an empty folder). 

[raw_results](./raw_results/) contains all the raw output from kiss-icp.
[corruption](./raw_results/corruption/) are the raw output on the corrupted data.
[denoise](./raw_results/denoise/) are the raw output on the denoised corrupted data using [Bilateral Filter](https://www.ipol.im/pub/art/2017/179/).
Under corruption or denoise, the folder name indicates the corruption type (it is the clean data if no corruption name). 

[eval_results](./eval_results/) contains the evaluation of the estimated poses on corrupted data and denoised corrupted data against the ground truth. 