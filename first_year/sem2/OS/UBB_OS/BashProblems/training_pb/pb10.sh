#!/bin/bash

for file in $@; do
	if [ -f $file ] && echo $file | grep -E -q "/*[^/\.]*\.c$"; then
		cat $file
	fi
done | grep -E "#include" > pb10_libs.txt 
