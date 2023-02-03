#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"


// TODO: function definitions here for ls2
//Function that recursively searches for a  file
int fileSearch(stack_t *s, char *path, char *fileName, int indent){
    DIR *dir;
    struct dirent* entry;
    char indentStr[MAX_NAME_LENGTH] = "\0";
    
    if(indent > 3) return 1;
    
    for (int i = 0; i < indent; i++){
        strcat(indentStr, INDENT);
    }
    //start by opening dir
    if ((dir = opendir(path)) == NULL)
        perror(path);
    //while there are still files
    while ((entry = readdir(dir)) != NULL){
        if (entry->d_type  == DT_DIR){
            char tmpstr[MAX_NAME_LENGTH] = "\0";
            strcpy(tmpstr, entry->d_name);
            
            if(strcmp(tmpstr, ".") !=0 && strcmp(tmpstr, "..") != 0){
                //control the push based on return value, then return the return value
                //define nPath as big then strcpy into it
                char nPath[MAX_NAME_LENGTH] = "\0";
                
                
                strcpy(nPath, strdup(path));
                strcat(nPath, "/");
                strcat(strcat(nPath,entry->d_name),"/");
                printf("\nRunning file search on %s, using string %s\n", path, nPath);
                fileSearch(s, nPath, fileName, indent + 1);
                char pushstr[MAX_NAME_LENGTH] = "\0";
                strcpy(pushstr, strdup(strcat(indentStr, entry->d_name)));
                printf("\nPush string is %s", pushstr);
                push(s, pushstr);
                
                }
        }
        //if its a directory construct the string, pop it on then recurse on it
        else if (entry->d_type == DT_REG){
            char tmpstr[MAX_NAME_LENGTH] = "\0";
            strcpy(tmpstr, entry->d_name);
            char nPath[MAX_NAME_LENGTH] = "\0";
            strcat(strcpy(nPath, strdup(path)), "\\");
            char *pushstr = strdup(nPath);
            push(s, pushstr);
        }
        //if its a file, construct the string and pop the string on
    
    }
    closedir(dir);
    return 0;
}

void mode1Recurse(stack_t *s, char *path, int indent){

}
