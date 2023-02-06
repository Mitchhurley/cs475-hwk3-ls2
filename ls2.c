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
    struct stat statbuf;
    char indentStr[MAX_DEPTH] = "\0";
    char newpath[MAX_NAME_LENGTH];
    int found = FALSE;
    
    
    for (int i = 0; i < indent; i++){
        strcat(indentStr, INDENT);
    }
    //start by opening dir
    if ((dir = opendir(path)) == NULL){
        //if there is an error print out issue
        perror("Directory could not be found or opened");
        return 0;}
    //while there are still files
    while ((entry = readdir(dir)) != NULL){
        if (entry->d_type  == DT_DIR){
            
            //ignoring the current
            
            if(strcmp(entry->d_name, ".") !=0 && strcmp(entry->d_name, "..") != 0){
                char pushstr[MAX_NAME_LENGTH];
                //control the push based on return value, then return the return value
                
                
                snprintf(pushstr, sizeof(pushstr), "%s%s/ (Directory)", indentStr, entry->d_name);
                //compose the new path
                snprintf(newpath, sizeof(newpath), "%s/%s", path, entry->d_name);
                if (fileSearch(s, newpath, fileName, indent + 1) == TRUE){

                    snprintf(pushstr, sizeof(pushstr), "%s%s/", indentStr, entry->d_name);

                    //char *tmp = (char*) malloc(sizeof(pushstr));
                    //strcpy(tmp, strdup(pushstr));
                   
                    push(s, pushstr);
                    found = TRUE;
                    }
                                
                }
        }
        //if its a directory construct the string, pop it on then recurse on it
        else if (entry->d_type == DT_REG){
            if (strcmp(fileName,entry->d_name) == 0){
                char nPath[MAX_NAME_LENGTH] = "\0";
                snprintf(nPath, sizeof(nPath), "%s/%s", path, entry->d_name);
                //TODO fix
                if (lstat(nPath, &statbuf) == -1) {
                        perror("lstat");
                        closedir(dir);
                        return 0;}
                char tmpstr[MAX_NAME_LENGTH] = "\0";
                unsigned long long bytes = statbuf.st_size;
                snprintf(tmpstr, sizeof(tmpstr),"%s%s (%llu)", indentStr, entry->d_name, bytes);
                push(s, tmpstr);
                found = TRUE;
            }
        }
        
    
    }
    closedir(dir);
    return found;
    
}

int mode1Recurse(stack_t *s, char *path, int indent){
    DIR *dir;
    struct dirent* entry;
    struct stat statbuf;
    char indentStr[MAX_DEPTH] = "\0";
    char newpath[MAX_NAME_LENGTH];
    
    
    for (int i = 0; i < indent; i++){
        strcat(indentStr, INDENT);
    }
    //start by opening dir
    if ((dir = opendir(path)) == NULL){
        //if there is an error print out issue
        perror("Directory could not be found or opened");
        return 0;}
    //while there are still files
    while ((entry = readdir(dir)) != NULL){
        if (entry->d_type  == DT_DIR){
            
            //ignoring the current
            
            
            if(strcmp(entry->d_name, ".") !=0 && strcmp(entry->d_name, "..") != 0){
                char pushstr[MAX_NAME_LENGTH];
                //control the push based on return value, then return the return value
                
                
                snprintf(pushstr, sizeof(pushstr), "%s%s/ (Directory)", indentStr, entry->d_name);
                //compose the new path
                snprintf(newpath, sizeof(newpath), "%s/%s", path, entry->d_name);
                char *tmp = (char*) malloc(sizeof(pushstr));
                strcpy(tmp, strdup(pushstr));
                snprintf(pushstr, sizeof(pushstr), "%s%s/", indentStr, entry->d_name);
                push(s, tmp);
                mode1Recurse(s, newpath, indent + 1);
                                
                }
        }
        //if its a directory construct the string, pop it on then recurse on it
        else if (entry->d_type == DT_REG){
            char nPath[MAX_NAME_LENGTH] = "\0";
            snprintf(nPath, sizeof(nPath), "%s/%s", path, entry->d_name);
            if (lstat(nPath, &statbuf) == -1) {
                    perror("lstat");
                    closedir(dir);
                    return 0;}
            char tmpstr[MAX_NAME_LENGTH] = "\0";
            unsigned long long bytes = statbuf.st_size;
            snprintf(tmpstr, sizeof(tmpstr),"%s%s (%llu)", indentStr, entry->d_name, bytes);
            push(s, tmpstr);
        }
        //if its a file, construct the string and pop the string on
    
    }
    closedir(dir);
    return 0;
}
