#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Please provide one directory"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "$1 is not a valid directory"
	exit 1
fi

s=0
for f in $(ls $1); do
	if [ -f "$1/$f" ]; then
		((s+=$(du -b "$1/$f" | awk '{print $1}')))
	fi
done
echo $s
