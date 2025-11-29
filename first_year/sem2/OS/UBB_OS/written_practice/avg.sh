#!/bin/bash

for f in `find`; do
    if [ -d $f ];then
        nr=`ls -al $f | grep -E -i -c "^.*\.txt"`
        nrfis=`ls -al $f | grep -E -i -c ".*"`
        avg=$((nrfis/nr))
        echo $avg pentru directory $f
    fi
done
