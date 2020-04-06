/*Tim Kuelker
 * C Program that takes in command line strings, displays them in reverse order,
 * then finds the smallest and largest lexographically, and displays them as well.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	int i = argc - 1;
	char *l, *s;

	//making sure there is at least one argument being passed in
	if(argc <= 1)
		printf("\nNeed some arguments for this program to run properly!\n\n");
	else{
		printf("\nCommand line arugments in reverse are:\n\t");

		/*Giving the pointers holding the largest and smallest variable something
		that can be compared*/
		l = argv[i];
                s = argv[i];

		/*displaying the argv array from last subscript to first, leaving out the 
		execute command and null terminator*/
		while(i > 0){

			/*If current value is smaller than current smallest, redeclare smallest*/
			if (strcmp(argv[i], s) < 0)
				s = argv[i];

			/*If current value is larger than current largest, redeclare largest*/
			if (strcmp(argv[i], l) > 0)
				l = argv[i];

			//printing the argument last iputed, then de-incrementing i
                        printf("%s ", argv[i--]);
		}
		
		printf("\n\nSmallest string lexicographically is: %s", s);
		printf("\nLargest string lexicographically is: %s\n\n", l);
	}

return EXIT_SUCCESS;
}

