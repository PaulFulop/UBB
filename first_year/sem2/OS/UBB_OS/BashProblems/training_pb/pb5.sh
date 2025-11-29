#!/bin/bash

for f in $@; do
	du -sb $f
done | sort -n 
