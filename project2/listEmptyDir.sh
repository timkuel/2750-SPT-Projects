#!/bin/bash
#Tim Kuelker

##Bash script that checks wether a directory is empty or not.
##If not empty, display the contents.
##If empty, write that directory name to a file.


dir=$1

##if dir is a directory
if [[ -d $dir ]]
then
	##if you can list things inside dir, then true
	if [[ "$(ls -A $dir)"  ]]
	then
		##lists contents of non empty directory
		echo "$dir is not empty, here are the contents:"
		ls $dir
		exit 0
	else
		##store the directory to file
		echo "$dir is an empty directory"
		echo "$dir" >>  EmptyDir.txt
		exit 0
	fi

else
echo "Usage: $0 [directory]"
exit 1;
fi

