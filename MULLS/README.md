## MULLS
MULLS is a c++ project which has many system-level dependencies. 
The Dockerfile provided by the official git repo has outdated due to the dependencies. 
We modified it a little bit so it can build successfully.
Please check [our cloned repo](https://github.com/boyang9602/MULLS) for the docker image build. 

### Steps
1. `docker build . --tag mulls`
2. `docker run --rm -it -v <dataroot>:/MULLS/data -v ./output:/MULLS/output mulls /bin/bash`
3. inside the docker container, `bash run.sh`

[raw_results](./raw_results/) contains all the raw output from MULLS.
[corruption](./raw_results/corruption/) are the raw output on the corrupted data.
[denoise](./raw_results/denoise/) are the raw output on the denoised corrupted data using [Bilateral Filter](https://www.ipol.im/pub/art/2017/179/).
Under corruption or denoise, the folder name indicates the corruption type (it is the clean data if no corruption name). 

[eval_results](./eval_results/) contains the evaluation of the estimated poses on corrupted data and denoised corrupted data against the ground truth. 
