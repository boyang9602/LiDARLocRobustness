#!/bin/bash

DATAROOT=$1

seqs=( "09" "10" )
datasets=($(ls $DATAROOT))

for seq in ${seqs[@]}
do
    for dataset in ${datasets[@]}
    do
        if [ ! -d $DATAROOT/$dataset/$seq ]; then
            continue
        fi
        calib_cmd="python calib.py $DATAROOT/$dataset/$seq/frame_poses.txt $DATAROOT/$dataset/$seq/calib_poses.txt"
        # echo $calib_cmd
        eval $calib_cmd
        end_frame="201"
        if [[ $seq == "09" ]]; then
            end_frame="401"
        fi
        cmd="./eval_seq $dataset $seq $DATAROOT/$dataset/$seq/calib_poses.txt 0 $end_frame"
        echo $cmd
        eval $cmd
    done
done
