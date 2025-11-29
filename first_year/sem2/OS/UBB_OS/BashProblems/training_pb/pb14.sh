#!/bin/bash

sum=0
count=0
user=""
prev_user=""

for pid in $(ps -ef | awk 'NR > 1{print $1","$2}' | sort); do
	if [ "$user" != "$prev_user" ]; then
		if [ $count -gt 0 ]; then
			echo "The mean of the pids for the user $prev_user is $((sum/count))"
		fi
		sum=0
		count=0
		prev_user=$user
	fi

	user=$(echo "$pid" | awk -F, '{print $1}')
	value=$(echo "$pid" | awk -F, '{print $2}')
	sum=$((sum+value))
	((count+=1))
done
