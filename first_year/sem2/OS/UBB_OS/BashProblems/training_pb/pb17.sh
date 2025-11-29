#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid number of arguments!"
	exit 1
fi

dir=$1

if [ ! -d $dir ]; then
	echo "Argument is not a directory!"
	exit 1
fi

for file in $(ls $dir); do
	if echo $file | grep -E -q ".c$"; then
		rm "$dir/$file"
	else
		echo $file
	fi
done | sort
