#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

#define SHM_KEY 0x1596
jmp_buf buf;

void killHandler(int);

void displayUsage(char *);

//Struct to hold the data
struct shmseg {
	int prime;
};

int pidRunner(struct shmseg *, char *, int);
  
int main(int argc, char *argv[]) {
	int i, j, pid, shmId, primer;
	struct shmseg *shmPtr;

	signal(SIGINT, killHandler);
	signal(SIGTSTP, killHandler);

	if(argc > 1){
		if(strcmp(argv[1], "-h") == 0){
			printf("\n\nOPTION FOR HELP SELECTED\n\n");
			displayUsage(argv[0]);
			exit(EXIT_SUCCESS);
		}
	}

	shmId = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
        if(shmId == -1){
                perror("Shared memory");
                exit(EXIT_FAILURE);
        }

	// Attaching to the mem segment to get pointer
	shmPtr = shmat(shmId, NULL, 0);
        if(shmPtr == (void *) -1){
                perror("Shared memory attach");
                exit(EXIT_FAILURE);
        }
	
	printf("\nIn Master:\tSetting Prime in the shared memory to 0.\n");

	//filling shared memory with 0  
	shmPtr->prime = 0;

        //If -n arguments passed in, and theres another agrument after it
	if(argc == 3){
		if(strcmp(argv[1],"-n") == 0){
                	primer = pidRunner(shmPtr, argv[2], shmId);

                	printf("\nIn Master:\tWorker has finished.\n");
                	printf("\n\n\tThe number %i is the LARGEST PRIME number LESS than %s.\n",primer, argv[2]);
		}
		else{
			displayUsage(argv[0]);
			exit(EXIT_SUCCESS);
		}
	}
        //else, run pidRunner with 100 as the default
	else{
		primer = pidRunner(shmPtr, "100", shmId);

                printf("\nIn Master:\tWorker has finished.\n");
        	printf("\n\n\tThe number %i is the LARGEST PRIME number LESS than 100.\n",primer);
        }
		
	printf("\nDetatching pointer and clearing the shared memory segment.\n\n");
        shmdt(shmPtr);
        shmctl(shmId, IPC_RMID, NULL);

	return 0;
}

int pidRunner(struct shmseg * shmPtr,char * num, int shmId){
	int primer, j, statuscode, pid;

	//If signal was caugh, jump UP THE CALL STACK to here
	//setjmp can only jump up the call stack.
	if(setjmp(buf) == 1){
                kill(pid,SIGKILL);
                shmdt(shmPtr);
                shmctl(shmId, IPC_RMID, NULL);
                exit(EXIT_SUCCESS);
        }

	pid = fork();
        if(pid == -1){
        	perror("Failed to fork");
                exit(EXIT_FAILURE);
        }

        if(pid == 0){
        	execl("./worker",num,NULL);
        	//only reached if execl fails
        	perror("Problem with excel");
        }
        else{
        	while(shmPtr->prime == 0){
                	printf("\nIn Master:\tWATCHING shared memory...\n\n\tWaiting for Prime to CHANGE FROM 0.\n");
              		sleep(1);
		}

                sleep(1);
                printf("\nIn Master:\tWATCHING shared memory...\n\n\tPrime WAS CHANGED FROM 0, it is NOW %i\n", shmPtr->prime);
                primer = shmPtr->prime;

                printf("\nIn Master:\tCHANGING the value of Prime TO 0.\n");
                shmPtr->prime = 0;

                wait(&statuscode);
	}

	//If Worker failed in someway
	if(statuscode != 0){
                printf("\nThe Worker FAILED! Possibly due to Prime not being initilized to 0.\n");
                printf("\n\tUnable to calculate LARGEST PRIME that is LESS than 100.\n");
                printf("\nTerminating child process if still running, detatching pointer, and clearing the shared memory segment.\n\n");
        	longjmp(buf,1);
	}

	return primer;
}

//Function that displays usage message
void displayUsage(char * argv){
        printf("\nUsage: %s [-n] [integer]\n\t\t[-h]\t\t:Option for help.\n", argv);
        printf("\nProgram takes in an integer and looks for the highest prime less than that integer.\n");
        printf("If no [-n] [integer] is provided, the program will automatically\n");
        printf("look for the largest prime less than 100.\n\n");
}

//handles signal
void killHandler(int dummy){
	printf("\n\nControl-C or Control-Z was pressed!\n");
        printf("\nTerminating child process if still running, detatching pointer, and clearing the shared memory segment.\n\n");
	longjmp(buf,1);	
}

