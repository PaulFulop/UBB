#!/bin/bash

sum=0
nr=0
avg=0

for f in `find ./ -name "*.sh"`;do
    nr=$((nr+1))
    result=`cat $f | grep -E -i -c -v "^#|^$"`
    sum=$((sum+result))
done

avg=$((sum/nr))
echo $avg
