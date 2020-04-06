!/bin/bash
## Timothy Kuelker
## Uses grep to search a pattern inside of the here document
## Loops through continuously until user enters control + c

x=""
##loop runs until a break command is entered
while [[ true ]]
do
	echo -e "\nEnter a regex to search the HERE document for, or hit CTR-C to exit"
	read x
	##checking if pattern is in the here document
	if grep -i "$x" << HERE
	John Doe, jdoe@great.com, 800-555-1111, California
	Jane Doe, jand@super.edu, 876-555-1321, New York
	John Smith, bsmith@fast.net, 780-555-1234, Florida
	Paul Wang, pwang@cs.kent.edu, 330-672-9050, Ohio
HERE
	then
		echo -e "\nFound some matches to the pattern, there they are.\n"
	else
		echo -e "\nThe match couldnt be found in the HERE document, try another!"
	fi

done
exit 0

