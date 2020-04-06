#!/bin/bash

#Tim Kuelker

#Script that takes in any amount of command line arguments and calculates 
#average 'test' score of arguments

score=0
firstname=$1
lastname=$2
#shifting the name arguments out of the way
shift
shift

fullname=$firstname" "$lastname
#setting tests to number of current command-line arguments to get number
#of testes entered to calculate average
tests=$#

#run while number of command line arguments are not 0
while [ $# -ne 0 ]
do
	#add the test score to first argument then shift
	score=$((score + $1))
	shift
done

average=$((score/tests))
if [ $average -lt 70 ]
then
        echo -e "\nBetter luck next time $fullname, you failed the class with an average score of $average\n"
        exit 0
fi
echo -e "\nCongratulations $fullname, you passed the class with an average score of $average\n"
exit 0

