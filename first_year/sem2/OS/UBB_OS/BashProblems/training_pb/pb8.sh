#!/bin/bash

if [ $# -lt 2 ] || [ $(($# % 2)) -eq 1 ]; then
	echo "Invalid number of arguments!"
	exit 1
fi

while [ $# -ne 0 ]; do
	if [ ! -f $1 ]; then
        	echo "$1 is not a file"
	else
		word_count=$(cat $1 | grep -E -i -o "\<$2\>" | wc -l)
		if [ $word_count -gt 2 ]; then	
			echo "$1 does contain the word $2 at least 3 times"
		else
			echo "$1 does not contain the word $2 at least 3 times"
		fi
	fi
	shift 2
done
