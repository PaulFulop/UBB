#!/bin/bash

if [ $# -gt 1 ]; then
	echo "Invalid number of arguments"
	exit 0
fi

if [ $# -eq 0 ]; then
	dir="."
else
	dir=$1
fi

if [ -d $dir ];then
	for f in $(find $dir -type f | grep -E "/[^/]*-[^/]*$"); do
		new_f=`echo $f | awk -F/ '{print $NF}' | sed -E "s/-/_/g"`
		parent_dir=`echo $f | sed -E "s,/[^/]*$,,"`
		cp $f "$parent_dir/$new_f"
	done
else
	echo "Not a directory"
fi
