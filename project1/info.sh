#!/bin/bash

#Tim Kuelker

#This script requires user to enter a [textFile] followed by a [directory]

#This script gives basic info about the running script, the user
#running the script, and some other general information that may be useful
#to know.  The commands used are pretty much explained with the echo
#statements.  If anything needed to be explained upon further, it will be
#in a comment above the executed code.

file="$1"
dir="$2"

#case statement that uses number of parameters as value. Script only runs
#if 2 parameters are entered.
case $# in
2)	
		#checking whether each parameter entered corresponds
		#to the proper type desired.
        if [[ -f $file && -d $dir ]]
        then
		#gives the name of the script file without the prefixes
	echo -e "\nThe current running script is: ${0##*/}"

        echo -e "\nThe current date and time is $(date)"
                
        echo -e "\nCurrent user is: $USER"
                #display current directory without prefixes
        echo -e "\nCurrent directory is: ${PWD##*/}"
		
	echo -e "\nThe name of UNIX machine is: $(uname)"
		
        echo -e "\nThe current login shell is: $(hostname)"

        echo -e "\nContents of $file: "; cat $file

        echo -e "\nNumber of lines in $file: $(wc -l < $file)"
                    
        echo -e "\nListings of $dir:"; ls $dir

        echo -e "\nThe total number of parameters used: $#"

        echo -e "\nCalender for October, 2019:"; (cal 10 2019)

        echo -e "\nThe disk usage of current script is:"; (du -h $0) 

	echo -e "\nNumber of users in the system: $(users | wc -w)"
	exit 0
        else
                #output message if parameters were not desired types
        echo -e "\nEither $file is not a file, or $dir is not a directory."
        echo "Make sure entering in proper order, fileName dirName."
	exit 127
        fi
        ;;

	#if not exactly two arguments passed in, display usage message
*)      echo "usage: $0 [fileName] [dirName]"
	exit 127
esac

