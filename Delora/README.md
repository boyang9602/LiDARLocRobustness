## Delora
Delora is a python project and [the official git repo](https://github.com/leggedrobotics/delora) provides a nice installation guide in conda env. 
We modified the code a little bit
1. The pre-trained model contains the configs which will override the configs from the file. We force it to use the configs from the file.
2. We removed the rosbag related import statements because we are not going to use rosbags.
3. We changed the config files. 
Please clone [our modified code](https://github.com/boyang9602/delora) and follow the instructions in the repo to install it. 

[raw_results](./raw_results/) contains the estimated poses by Delora. [corruption](./raw_results/corruption/) contains the results on the corrupted data. [denoise](./raw_results/denoise/) contains the results on the denoised corrupted data using [Bilateral Filter](https://www.ipol.im/pub/art/2017/179/). [retrain](./raw_results/retrain/) contains the results of retrained Delora on the augmented data. 
The name rules are <whatever>_poses_text_file_kitti_<corruption>_<severity>_<sequence>.txt

[eval_results](./eval_results/) contains the calculated relative pose error (RPE) for each corruption. 

[config_gen.sh](./config_gen.sh) is a script to generate the run configs, either for evaluation or re-training. It accepts 2 args, the first one is the folder of the corruption datasets, and the second one should be either "train" (will specify the train sequences to be 00 to 08 and leave "test" to be empty) or "test" (will specify the sequences to be 09 and 10 and leave train to be empty). It will further specify the datasets in the deployment_options.yaml. Please put it under the root of Delora and run it. 

# How to run?
We provide a [config_gen.sh](https://github.com/boyang9602/delora/blob/main/config_gen.sh) which can generate the configs for all corrupted and the clean dataset. It requires 2 args, the first one is the root of the datasets and the second one is the mode, should be either "test" or "train". "train" will specify the train sequences to be 00 to 08 and leave "test" to be empty, while "test" will specify the test sequences to be 09 and 10 and leave train to be empty.

After you generated the config, you need to preprocess the data first: 
```
python bin/preprocess_data.py
```

Then you can run train by
```
python bin/run_training.py --training_run_name <your train name> --experiment_name <your experiment name> --checkpoint checkpoints/kitti_example.pth | checkpoints/retraining_w_clean_checkpoint_epoch_5.pth
```
kitti_example.pth is the pre-trained model provided by Delora team and retraining_w_clean_checkpoint_epoch_5.pth is the re-trained model based on the pre-trained model on the augmented data. 

You can run test by 
```
python bin/run_training.py --test_run_name <your test name> --experiment_name <your experiment name> --checkpoint checkpoints/kitti_example.pth | checkpoints/retraining_w_clean_checkpoint_epoch_5.pth
```
