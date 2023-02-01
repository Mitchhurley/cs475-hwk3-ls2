#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"


// TODO: function definitions here for ls2
//Function that recursively searches for a  file
bool fileSearch(stack_t *s, char *path, char *fileName, int indent){
    DIR *dir;
    struct dirent* entry;
    //start by opening dir
    if ((dir = opendir(path)) == NULL)
        perror("opendir() error");
    //while there are still files
    while ((entry = readdir(dir)) != NULL){
        //if its a directory, recurse on it
        
        //if its a file, construct the string and pop the string on
    
    }
}
DIR* readDir(stack_t *s, char *path, int indent){

}
void mode1Recurse(stack_t *s, char *path, int indent);
