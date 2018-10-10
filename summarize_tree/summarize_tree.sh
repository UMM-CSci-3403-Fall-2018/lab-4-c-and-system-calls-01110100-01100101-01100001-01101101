#!/bin/bash

#assign directory to the imput
DIR=$1

#cd into the target directory
cd $DIR

#count directory using find & wc
num_dirs=$(find . -type d | wc -l)

#count regular files using find & wc
num_regular=$(find . -type f | wc -l)

#print our results
echo "There were $num_dirs directories."
echo "There were $num_regular regular files."
