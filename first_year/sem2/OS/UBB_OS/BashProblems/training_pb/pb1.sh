#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Not enough arguments"
	exit 0
fi

dir=$1

if [ ! -d $dir ]; then
	echo "Not a directory"
	exit 0
fi

find $dir -type f | grep -E "/[^/.]*\.c$" | wc -l 
