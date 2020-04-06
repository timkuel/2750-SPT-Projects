#!/bin/bash

#Tim Kuelker

#This shell script takes in a value from 10 to 100 and
#calculates the smallest prime factor of that number.

low=10
high=100
n=0

echo "Enter an integer from 10-100 to calculate its smallest prime factor"
read n

#determining wether the entered num
if [[ $n -ge $low && $n -le $high ]]
then
		#take factor of $x, pipeline to awk, which helps
		#organize the factor command into aguments, and stores the
		#printed value of second argument into test	
	test=`factor $n | awk '{print $2}'`
	
	#if entered integer is equal to the factor, then it is prime	
	if [[ $n -eq $test ]]
	then
		echo "$n is a prime number"
	else
		echo "$test is the smallest prime factor of $n"
	fi
	
else
	echo "$n is not in the range from 10-100"
fi

