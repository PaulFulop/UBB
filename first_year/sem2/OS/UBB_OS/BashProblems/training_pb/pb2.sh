#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Invalid amount of args"
	exit 1
fi

s=0

for f in $(find $1 -type f | grep -E "/[^/.]*.c$"); do
	lnc=$(cat $f | wc -l)
	((s+=$lnc))
done

echo $s
