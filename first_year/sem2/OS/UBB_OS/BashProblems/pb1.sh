#!/bin/bash

if [ $# -ne 2 ];then
	echo "invalid number of arguments"
	exit 0
fi

D=$1
n=$2
N=$(($2 * 9 / 10))

if [ -d $D ];then
	bytes=`du -bs $D | awk '{print $1}'`
	
	if [ $bytes -gt $n ];then
		echo "We have $bytes > $n"
	elif [ $bytes -gt $N -a $bytes -lt $n ];then
		echo "The number of bytes ($bytes) > 90% ($N) of n ($n) but its also less than n."
	else
		echo "The number of bytes is smaller than 90% of ($n)."
	fi
	exit 0
fi
