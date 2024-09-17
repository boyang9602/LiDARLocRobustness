# LiDARLocRobustness
This repo serves as the replication package for the paper "Evaluating and Improving the Robustness of LiDAR-based Localization and Mapping". 
We generated 18 types of corruptions for KITTI Odometry LiDAR scans and evaluated 4 SOTA LiDAR-only SLAM systems and one SOTA LiDAR-based global localization system. 

# Corruption LiDAR data generation
Since the generated LiDAR corruption data is too large, it is impractical to share them directly. 
Please refer to [our code](https://github.com/boyang9602/perturb_pointcloud) for generating corrupted LiDAR data.  

# Subject Systems
In this work, we studied the robustness of four LiDAR-only SLAM systems, 
[MULLS](https://github.com/YuePanEdward/MULLS), 
[kiss-icp](https://github.com/PRBonn/kiss-icp), 
[Delora](https://github.com/leggedrobotics/delora) and 
[NeRF-LOAM](https://github.com/JunyuanDeng/NeRF-LOAM), 
and one LiDAR-based map-based global localization, 
[LocNDF](https://github.com/PRBonn/LocNDF). 

The instructions for replicating the evaluation in our paper, as well as the necessary code are provided under the corresponding folder. 

# Experiment Results
We uploaded the raw results, i.e., the poses produced by subject systems, and the evaluation results, i.e., relative pose errors (RPE), under the corresponding folder. 

The figures used in the paper are generated at https://colab.research.google.com/drive/1KWtEsUrdcGOSuh7NxSEXOpzioMnWu1JQ?usp=sharing. 
