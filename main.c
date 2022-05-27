#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compresor.c"

int main(int argc, char **argv){

    if(!strcmp(argv[1], "C") && argv[2] != NULL){
        achicatte(argv[2]);
    }

}