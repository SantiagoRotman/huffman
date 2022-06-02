#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compresor.h"
#include "io.h"
#include "decompressor.h"

#include <time.h>


int main(int argc, char **argv){

    if(argc != 3) {
        printf("Comprimir: ./main.c C 'file.txt'\n");
        printf("Descomprimir: ./main.c D 'file.txt.hf'\n");
        return 1;
    }

    if(!strcmp(argv[1], "C") && argv[2] != NULL){
        achicatte(argv[2]);
    }

    if(!strcmp(argv[1], "D") && argv[2] != NULL){
        char treePath[100];
        strcpy(treePath, argv[2]);
        strcpy(treePath + strlen(argv[2])-3, ".tree");
        char decPath[100];
        strcpy(decPath, argv[2]);
        strcpy(decPath+ strlen(argv[2])-3, ".dec");
        decompresor(argv[2], treePath, decPath);
    }

    if(!strcmp(argv[1], "crear") && argv[2] != NULL){
        FILE * f=  fopen("AllInOne", "w");
        srand((unsigned) time(NULL));
        for(int i = 0; i < 10000; i++){
            fputc((char) (rand()%256) , f);
        }
        fclose(f);
    }
    return 0;

}
