/*Author: Tim Kuelker
 *Date  : April 23, 2019
 *Description: Program that takes in command line arguments, one
 * of which is a file that needs to be read form, and the other
 * is a file that needs to be written to.  The program reads the input
 * file line by line, pushes values seperated by a space into a stack,
 * then writes each popped item to the output file as popped so it gets
 * written in reverse.  If the push function finds a duplicate varibale
 * in a line, it will not push that one in the stack again.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int main(int argc, char ** argv){
	Stack s1, s2;
	FILE *inFile, *outFile;
	char line[100];
	char *file_i, *file_o, *token;
	char c = ' ';
	int i = 0;

	for(i = 1; i < argc; i++){

		//If the [-h] option was selected	
		if(strcmp(argv[i], "-h") == 0){
			c = 'h';	
		}
		//If the [-1] option was selected
		if(strcmp(argv[i], "-i")== 0){
			//If the [-o] option was also selected set c as 'g', otherwise c is 'i'
			if(c == 'o')
				c = 'g';
			else
				c = 'i';
			file_i = argv[i + 1];
		}
		//If the [-o] option was selected
		if(strcmp(argv[i], "-o") == 0){
			//If the [-i] option was also selected set c as 'g', otherwise c is 'o'
			if(c == 'i')
				c = 'g';
			else
				c = 'o';
			file_o = argv[i + 1];
		}
	}

	//If c = 'i' then only an input file was given, make 'output.txt' the default output file. Set c as 'g'.
	if(c == 'i'){
		file_o = "output.txt";
		c = 'g';
	}

	switch(c){
		case 'h':
			printf("\nOption '-h' for HELP selected.\n");
			printf("\n[-i]\t:\tprecursor for [inFile]\n[-o]\t:\tprecursor for [outFile]\n[-h]\t:\thelp option\n");
			printf("\nNote: [-i] [inFile] and [-o] [outFile] can come in any order,\nas long as the proper precursor is used. ");
			printf("If no [-o] [outFile] is provided,\n'output.txt' will be used by default.\n");
			printf("\nUsage: %s  [-i] [inFile] [-o] [outFile]\n\n", argv[0]);
			break;
		case 'o':
                        printf("\nAn [-o] [outFile] was provided, but a [-i] [inFile] was not.\n");
                        printf("\nUsage: %s  [-i] [inFile] [-o] [outFile]\n\n", argv[0]);
                        break;
		case 'g':
			//Creating stack object
			s1 = create();
		
			//Opening the inFile
			inFile = fopen(file_i,"r");
			
			//If failed to open
			if(inFile == NULL){
				printf("\nThe [inFile] could not be opened, exiting\n\n");
				return EXIT_FAILURE;
			}

			//Opening the outfile
			outFile = fopen(file_o,"w");
	
			//If failed to open
			if(outFile == NULL){
				printf("\nThe [outFile] could not be opened, exiting\n\n");
                                return EXIT_FAILURE;
			}

			//While reading file line by line, do stuff inside.
			while(fgets(line, sizeof(line), inFile)){
				//strtok is allowing the program to split the line into tokens, using the delimiter " ", which is a space.
				token = strtok(line, " ");

				//Pushing token into the stack
				push(s1, atoi(token));

				//While there are still tokens, push rest into stack
				while((token = strtok(NULL, " ")) != NULL){
					push(s1, atoi(token));
				}
				
				//While the stack is not empty, write the popped variable to an outfile.
				while(!isEmpty(s1)){
					fprintf(outFile,"%i " ,pop(s1));
				}
				//Entering a new line in the file
				fprintf(outFile,"\n");
			}
	
			//Destroying stack, and closing files.
			destroy(s1);
			fclose(inFile);
			fclose(outFile);

			printf("\nEverything appeared to be successful! Check file '%s' to double check.\n\n", file_o);
                        break;
		default:
			printf("\n[-i]\t:\tprecursor for [inFile]\n[-o]\t:\tprecursor for [outFile]\n[-h]\t:\thelp option\n");
                        printf("\nNote: [-i] [inFile] and [-o] [outFile] can come in any order,\nas long as the proper precursor is used. ");
                        printf("If no [-o] [outFile] is provided,\n'output.txt' will be used by default.\n");
                        printf("\nUsage: %s  [-i] [inFile] [-o] [outFile]\n\n", argv[0]);
	}
	
	return EXIT_SUCCESS;
}

