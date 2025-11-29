#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Provide at least one program name"
	exit 1
fi

snapshot=$(ps -ef)
current_snapshot=""
while true; do
	sleep 2
	current_snapshot=$(ps -ef)

	if ["$current_snapshot" != "$snapshot" ]; then
		for prog in $@; do
			if echo $current_snapshot | grep -E -q "$prog"; then
#incomplete


