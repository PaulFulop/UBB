#!/bin/bash

if [ $# -gt 1 ]; then
	echo "Invalid number of arguments"
	exit 1
fi

dir="."
if [ -d $1 ]; then
       dir=$1
fi

for f in $(ls $dir); do
	if [ -f $f ] && file $f | grep -E -q "text"; then
		echo "$f: The filesize is $(du -sb "$dir/$f" | awk '{print $1}') bytes, permissions are $(ls -l "$dir/$f" | awk '{print $1}'), and the number of unique lines is $(cat "$dir/$f" | sort | uniq | wc -l)"
	fi
done		
