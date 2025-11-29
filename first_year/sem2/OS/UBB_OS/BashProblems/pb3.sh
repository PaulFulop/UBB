#!/bin/bash

for arg in $@; do
	if [ -f $arg ]; then
		du -sb $arg
	fi
done | sort -nr | uniq
