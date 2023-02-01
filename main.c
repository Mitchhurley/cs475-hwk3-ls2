#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	// stack stores the lines to print out
	stack_t *s = initstack();

	push(s, "Hello1");
	push(s, "Hello2");
	push(s, "Hello3");

	// print stack
	printstack(s);

	// free up stack
	freestack(s);
	return 0;

	/*
	if (argc == 3){
		//in the case of this, we need to create a stack and pass it through the recursive calls

	}
	else if (argc == 2){
		//make the stack
		// call  mode 1 recurse
		//print stack

	}
	else {printf("Usage: ./ls2 <path> [optional-file]\n");}
	return 0;
	
	
	*/
}
