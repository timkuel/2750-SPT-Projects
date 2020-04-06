#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define STACK_SIZE 100

struct stack_type{
	int contents[STACK_SIZE];
	int top;
};

static void terminate(const char *message){
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

Stack create(){
	Stack s = malloc(sizeof(struct stack_type));
	if(s == NULL){
		terminate("Error in create: stack could not be created.");
	}
	s->top = 0;
	return s;
}

void destroy(Stack s){
	free(s);
}

void makeEmpty(Stack s){
	s->top = 0;
}

bool isEmpty(Stack s){
	if(s->top == 0)
		return true;
	else
		return false;
}

bool isFull(Stack s){
	if(s->top == STACK_SIZE)
		return true;
	else
		return false;
}

//Searching linearly to see if value trying to push into stack is already contained within
bool isInside(Stack s, int n){
	int i;
	for(i = 0; i < s->top; i++){
		if(s->contents[i] == n){
			printf("\nItem alread inside the stack, not pushing: %i\n", n);
			return true;
		}
	}
	return false;
}

//This push function will only push non-duplicates into a stack.
void push(Stack s, int n){
	if(isFull(s)) {
		terminate("Error in push: stack is full.");
	}
	if(!isInside(s,n)){
		printf("\nItem being pushed into stack: %i\n", n);
        	s->contents[s->top++] = n;
	}
}

int pop(Stack s){
	if(isEmpty(s)) {
    		terminate("Error in pop: stack is empty.");
	}
	printf("\nItem being popped from stack: %i\n", s->contents[s->top - 1]);
	return s->contents[--s->top];
}

