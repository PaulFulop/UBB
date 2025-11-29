#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid number of arguments"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "Not a folder"
	exit 1
fi

interval=2
folder=$1
snapshot=$(ls -lR $folder)

while true; do
	sleep $interval
	new_snapshot=$(ls -lR $folder)

	if [ "$snapshot" != "$new_snapshot" ]; then
		snapshot=$new_snapshot
		echo "Something has changed!"
	fi
done
