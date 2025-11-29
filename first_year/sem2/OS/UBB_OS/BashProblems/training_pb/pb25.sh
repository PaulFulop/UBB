#!/bin/bash

if [ $# -eq 0 ]; then
	echo "No arguments"
	exit 1
fi

for item in $@; do
	if [ -f $item ]; then
		cat $item | head -10
	elif [ -d $item ]; then
		echo "$item is a directory."
		touch "$item/$item.info"
		ls -l $item > "$item/$item.info"
	else
		echo "The item is neither a directory or file"
	fi
done			
