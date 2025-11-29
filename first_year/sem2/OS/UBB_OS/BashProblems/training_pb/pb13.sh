#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Please provide one argument"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "Argument is not a directory"
	exit 1
fi

find $1 -type f | awk -F/ '{print $NF}' | sort | uniq -c
