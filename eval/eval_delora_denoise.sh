#!/bin/bash

DATAROOT=$1

datasets=($(ls $DATAROOT | grep .txt))


for filename in ${datasets[@]}
do
    len=${#filename}
    dataset=${filename:24:len-31}
    seq=${filename:len-6:2}
    cmd="./eval_seq $dataset $seq $DATAROOT/$filename"
    # echo $cmd
    eval $cmd
done
