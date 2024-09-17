#!/bin/bash

echo $(date)

docker ps | grep nerf

# Define the image name to filter by
IMAGE_NAME="nerf-loam-env"

# Get the current timestamp in seconds
CURRENT_TIME=$(date +%s)

# List all containers running from the specified image
docker ps --filter "ancestor=$IMAGE_NAME" --format "{{.ID}}" | while read -r container_id; do
    # Get the container start time using docker inspect
    START_TIME=$(docker inspect --format='{{.State.StartedAt}}' "$container_id")
    
    # Convert the start time to Unix timestamp
    START_TIMESTAMP=$(date -d "$START_TIME" +%s)
    
    # Calculate how long the container has been running
    RUNNING_TIME=$((CURRENT_TIME - START_TIMESTAMP))
    
    # Check if the container has been running for more than 6300 seconds
    if [ "$RUNNING_TIME" -gt 6300 ]; then
        container_name=$(docker inspect --format '{{.Name}}' "$container_id" | sed 's/\///')
        echo "kill $container_name which has been running for $(($RUNNING_TIME / 3600)) hours and $(($RUNNING_TIME % 3600 / 60)) minutes."
        docker kill $container_id
    fi
done

seqs=( "09" "10" )

for seq in ${seqs[@]}
do
    folder="NeRF-LOAM"
    if [ "$seq" == "10" ]; then
        folder="NeRF-LOAM2"
    fi
    
    docker_name="nerf_loam.*$seq"
    
    cuda_oom="RuntimeError: CUDA out of memory."
    bug_text="Encouter a bug"
    exceptions=( "$cuda_oom" "$bug_text" )
    
    for exc in "${exceptions[@]}"
    do
        echo "check $exc in /home/bo/projects/$folder/run$seq.log"
        if grep -q "$exc" /home/bo/projects/$folder/run$seq.log; then
            container_id=$(docker ps --filter "name=$docker_name" --format "{{.ID}}")
            container_name=$(docker ps --filter "name=$docker_name" --format "{{.Names}}")
            echo "Detected $exc error. Killing Docker container: $container_name ($container_id)"
            docker kill $container_id
            mv /home/bo/projects/$folder/run$seq.log /home/bo/projects/$folder/run$seq.$container_name.log
        fi
    done
done

echo "=========checking done========="
