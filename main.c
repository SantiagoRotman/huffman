#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compresor.h"
#include "io.h"
#include "decompressor.h"

#include <time.h>


int main(int argc, char **argv){

    if(!strcmp(argv[1], "C") && argv[2] != NULL){
        achicatte(argv[2]);
    }

    if(!strcmp(argv[1], "D") && argv[2] != NULL){
        char hfPath[100];
        strcat(strcpy(hfPath, argv[2]), ".hf");
        char treePath[100]; 
        strcat(strcpy(treePath, argv[2]), ".tree");
        char decPath[100]; 
        strcat(strcpy(decPath, argv[2]), ".dec");
        decompresor(hfPath, treePath, decPath);
    }

    if(!strcmp(argv[1], "crear") && argv[2] != NULL){
        FILE * f=  fopen("AllInOne", "w");
        srand((unsigned) time(NULL));
        for(int i = 0; i < 10000; i++){
            fputc((char) (rand()%256) , f);
        }
        fclose(f);
    }

}