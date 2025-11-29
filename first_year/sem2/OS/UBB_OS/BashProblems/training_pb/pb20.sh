#!/bin/bash

if [ $# -eq 0 ]; then
	echo "No words"
	exit 1
fi

file=""
while [ $# -ne 0 ]; do
	read -p "Insert a file here: " file

	if [ ! -f $file ];then
		echo "$file is not a file"
	else
		for word in $@; do
			if cat $file | grep -E -q "$word"; then
				echo "$word has been found in $file!"
				shift
			fi
		done
	fi
done

echo "All words have been found!"
