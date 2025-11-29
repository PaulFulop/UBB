#!/bin/bash

filename=""

while [ "$filename" != "stop" ]; do
	read -p "Enter the file name here: " filename
	if [ -f $filename ] && echo $filename | grep -E -q ".txt"; then
		cat $filename | head -1 | awk '{print NF}'
	else
		if [ "$filename" != "stop" ]; then
			echo "Not a valid file"
		fi
	fi	
done

echo "Done!"
