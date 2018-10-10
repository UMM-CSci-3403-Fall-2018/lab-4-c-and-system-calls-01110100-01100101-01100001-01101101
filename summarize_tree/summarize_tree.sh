#!/bin/bash

DIR=$1

cd $DIR

num_dirs=$(find . -type d | wc -l)

num_regular=$(find . -type f | wc -l)

echo "There were $num_dirs directories."
echo "There were $num_regular regular files."
