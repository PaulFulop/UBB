#!/bin/bash
#Write a bash script that receives as command line arguments if either files or directories. You must #check for each argument if it is a regular file and display the first 10 lines from it. If the argume#nt is a directory, create a file with the same name as the directory + ".info" and put the output of #the ls- l command in it. 
#
#if the argument is neither a regular file or directory, display a message.

while test $# -gt 0; do
	if test -f $1; then
		cat $1 | head -n 10	
	elif test -d $1; then
		file=`echo "$1" | awk -F/ '{print $NF}'`
		file="${file}.info"
		ls -l $1 > $file
	else
		echo "The argument $1 is neither a regular file nor a directory."
	fi
	shift
done
