#ifndef LS2_H_INCLUDED
#define LS2_H_INCLUDED

#include "stack.h"

#define TRUE 1
#define FALSE 0
#define INDENT "    "
#define MAX_NAME_LENGTH 20000

// TODO: Function declarations here for ls2

int fileSearch(stack_t *s, char *path, char *fileName, int indent);
void mode1Recurse(stack_t *s, char *path, int indent);
#endif
