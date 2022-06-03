#ifndef __DECOMPRESSOR_IO_
#define __DECOMPRESSOR_IO_
#include "resources.h"

/*
    readTree: char* int* int int* -> Btree

    Lee un arbol codificado y devuelve el arbol armado en forma de Btree.
*/
Btree *readTree(char *encodedTree, int *treeIndex, int enterPosition, int *letterIndex);

/*
    buildText: Btree* char* int* -> char

    Lee una cadena de 0's y 1's y con esas direcciones va
    recorriendo el arbol hasta llegar a una letra y la devuelve.
*/
char buildText(Btree *tree, char *encodedFileText, int *index);

/*
    decompresor: char* char* char* -> int

    Recibe nombres de archivos en los que esta el texto encodeado,
    el arbol encodeado y el nombre del archivo de salida.
*/
int decompresor(char *encodedTextPath, char *encodedTreePath, char *outputPath);

#endif