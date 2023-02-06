#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	// stack stores the lines to print out
	stack_t *s = initstack();
	
	
	if (argc == 3){
		fileSearch(s, argv[1],argv[2],0);
		printstack(s);
		freestack(s);
	}
	else if (argc == 2){
		//make the stack
		stack_t *rev = initstack();
		// call  mode 1 recurse with path (".")
		//print stack
		mode1Recurse(s, ".", 0);
		int number = s->size;
		//DOING
		for (int i = 0; i < number; i++){
			push(rev, pop(s));
		}	
		
		
		printstack(rev);
		freestack(s);
		freestack(rev);
		// free up stack
		
		//when printing stack in order to reverse it, push onto a new stack then print that

	}
	else {printf("Usage: ./ls2 <path> [optional-file]\n");}
	return 0;
	
	
	
}
