#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_KEY 0x1596

int isPrime(int);

struct shmseg {
	int prime;
};

int main(int argc, char *argv[]) {
        int i, primer, *prime, shmId;
        char choice;
	struct shmseg *shmPtr;
	
	primer = atol(argv[0]);

	printf("\nIn Worker:\tCalculating LARGEST PRIME that is LESS than %i\n", primer);

	//Checking all numbers one less than primer, to exclude that one, down to one if it is prime
	for(i = primer - 1; i > 1; i--){
		if(isPrime(i) == 1){
			primer = i;
			break;
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
        
	//if we cant read info from the pointer
	if(shmPtr->prime == -1){
		perror("read");
		exit(EXIT_FAILURE);
	}
	
	//if the Shared Memory location wasn't populated with 0
	if(shmPtr->prime != 0){
		printf("\nIn Worker:\tPrime is NOT SET TO 0, it is %i!\n\n\tExiting Worker!\n", shmPtr->prime);
		exit(EXIT_FAILURE);
	}

	printf("\nIn Worker:\tPEEKING into the shared memory we see Prime IS SET TO %i.\n",shmPtr->prime);
	printf("\nIn Worker:\tCHANGING the value of Prime FROM 0.\n");

	shmPtr->prime = primer;
	while(shmPtr->prime != 0){
		printf("\nIn Worker:\tWATCHING shared memory...\n\n\tWaiting for Prime to CHANGE BACK to 0.\n");
		sleep(2);
	}

	printf("\nIn Worker:\tWATCHING shared memory...\n\n\tPrime CHANGED FROM %i and is NOW %i AGAIN \n",primer, shmPtr->prime);

	if(shmdt(shmPtr) == -1){
		perror("shmdt");
		exit(EXIT_FAILURE);
	}
        shmctl(shmId, IPC_RMID, NULL);


	exit(EXIT_SUCCESS);
}

//Function that checks wether a number is prime or not
int isPrime(int number) {
        int i;
        for(i = 2; i < number; i++){
                if(number % i == 0 && i != number) return 0;
        }
        return 1;
}

