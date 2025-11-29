#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Invalid number of arguments!"
    exit 1
fi

if [[ -e $1 && (-r $1 || -w $1 || -x $1) ]]; then
    echo "The user has some permissions on the file!"
else
    echo "The user has no perms!"
fi
