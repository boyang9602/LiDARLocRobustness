## LocNDF
LocNDF is a python project with several system-level dependencies. [The official git repo](https://github.com/PRBonn/LocNDF) provides a nice installation guide. We modified the code a little bit
1. We added a few lines to write the raw results, i.e., predicted poses to files.
2. We added a few lines to parameterize the location of datasets
3. We added some scripts to run on all corrupted datasets. 
Please clone [our modified code](https://github.com/boyang9602/LocNDF) and install it by `pip install -e .`. 

[raw_results](./raw_results/) contains the raw poses estimated by LocNDF on all types of corruptsion, suggested by the folder name. 
[eval_resuls](./eval_results/) contains the errors compared to the ground truth. 

Since LocNDF is robust against all applied corruptions, we did not do any denosing or retraining. 