#!/bin/bash

for file in $@; do
	if [ -f $file ]; then
		du -sb $file
	fi
done | sort -nr
