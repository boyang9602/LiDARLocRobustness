#!/bin/bash

DATAROOT=$1
OUTPUTROOT=$2

seqs=( "09" "10" )
datasets=($(ls $DATAROOT))

for seq in ${seqs[@]}
do
    for dataset in ${datasets[@]}
    do
        export kiss_icp_out_dir=$OUTPUTROOT/$dataset/$seq
        cmd="kiss_icp_pipeline --dataloader kitti --sequence $seq $DATAROOT$dataset/dataset/"
        echo $cmd
        echo "Output is $kiss_icp_out_dir"
        eval $cmd
    done
done
