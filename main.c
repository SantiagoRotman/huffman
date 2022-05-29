#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compresor.h"
#include "io.h"
#include "decompressor.h"

int main(int argc, char **argv){

    if(!strcmp(argv[1], "C") && argv[2] != NULL){
        achicatte(argv[2]);
    }

    if(!strcmp(argv[1], "D") && argv[2] != NULL){
        char hfPath[100];
        strcat(strcpy(hfPath, argv[2]), ".hf");
        char treePath[100]; 
        strcat(strcpy(treePath, argv[2]), ".tree");
        decompresor(hfPath, treePath);
    }


}