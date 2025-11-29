#!/bin/bash

while [ ! $# -eq 0 ]; do
	if [ -f $1 ]; then
		echo "$1 is a file"
	elif [ -d $1 ]; then
		echo "$1 is a directory"
	elif echo $1 | grep -E -q "^[0-9]+$"; then
		echo "$1 is a number"
	else
		echo "$1 is something else"
	fi
	
	shift
done
