all:	master worker

master:		master.o
	gcc -o master master.o

worker:		worker.o
	gcc -o worker worker.o

master.o:	master.c
	gcc -c master.c

worker.o:	worker.c
	gcc -c worker.c

clean:
	rm -f *.o
