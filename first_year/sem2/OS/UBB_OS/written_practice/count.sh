#!/bin/bash

if [ $# -lt 1 ]; then
    echo "No arguments!"
fi

sum=0
for file in $@; do
    if [ -e $file ]; then
        length=`cat $file | wc -w`
        sum=$((sum + length))
    fi
done;

echo "$sum"
