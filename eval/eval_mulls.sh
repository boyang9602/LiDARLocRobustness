#!/bin/bash

set -e

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
        cmd="./eval_seq $dataset $seq $DATAROOT/$dataset/$seq/pose_b_lo_${dataset}.txt"
        # echo $cmd
        eval $cmd
    done
done
