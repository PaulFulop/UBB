#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid number of args"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "Not a directory"
	exit 1
fi

dir=$1

for file in $(find $dir -type l); do
	if [ ! -e $file ]; then
		echo "Link $file does not exist"
	fi
done
