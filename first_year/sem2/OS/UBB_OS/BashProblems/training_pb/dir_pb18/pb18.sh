#!/bin/bash

files=$(find . -type f | awk -F/ '{print $NF}')

for file in $files; do
	wperms=$(ls -l $file | awk '{print $1}' | grep -E -o "w" | wc -l)
	if [ $wperms -eq 3 ]; then
		echo $file
	fi

	chmod u-w,g-w,o-w $file
done
