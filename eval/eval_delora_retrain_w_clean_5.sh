#!/bin/bash

DATAROOT=$1

datasets=($(ls $DATAROOT | grep .txt))


for filename in ${datasets[@]}
do
    len=${#filename}
    dataset=${filename:34:len-41}
    seq=${filename:len-6:2}
    cmd="./eval_seq $dataset $seq $DATAROOT/$filename"
    # echo $cmd
    eval $cmd
done
