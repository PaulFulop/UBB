#!/bin/bash

fname=""

while [ ! -f "$fname" ]; do
	read -p "Insert the string here: " fname
done
