#!/bin/bash

DATAROOT=$1

seqs=( "09" "10" )
datasets=($(ls $DATAROOT))

for seq in ${seqs[@]}
do
    for dataset in ${datasets[@]}
    do
        if [ ! -d $DATAROOT/$dataset ]; then
            continue
        fi
        export kiss_icp_out_dir=$DATAROOT/$dataset/$seq
        cmd="./eval_seq $dataset $seq $kiss_icp_out_dir/latest/${seq}_poses_kitti.txt"
        # echo $cmd
        eval $cmd
    done
done
