#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Please provide a valid file"
	exit 1
fi

file=$1

if [ ! -f $file ]; then
	echo "Invalid file"
	exit 1
fi

emails=""
for user in $(cat $file); do
	emails="$emails,$user@scs.ubbcluj.ro"
done

echo $emails | sed -E "s/,//"
