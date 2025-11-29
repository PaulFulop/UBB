#!/bin/bash
#Write a bash script that receives as command line arguments pairs of arguments A and B.
#For each pair, if argument A contains argument B, display them

i=0
while [ $# -ge 2 ]; do
	a=$1
	b=$2

	if echo "$a" | grep -E -q "$b"; then
		echo "$b is indeed found inside $a"
	fi
	shift 2
done

if test $# -ne 0; then
	echo "Incomplete pair of arguments: $1 $2"
fi
