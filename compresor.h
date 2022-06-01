#ifndef __COMPRESOR_IO_
#define __COMPRESOR_IO_
#include "resources.h"

/*
    computeFrequency: Tuple* char* int -> void

    Esta funcion recibe un char* que lo va recorriendo y guardando en
    la tupla que recibe la frecuencia de aparicion de cada letra.
*/
void computeFrequency (Tuple *A, char *text, int len) ;

/*
    sortTuples: Tuple* int -> void

    Ordena un array de Tuples dependiendo de la frecuencia de aparicion
    de cada elemento.
*/
void sortTuples(Tuple *A, int len) ;

/*
    addInOrder: TreeList* Btree* -> TreeList*

    Dado una TreeList y un nuevo elemento para agregar,
    se agrega a la lista sin perder el orden de los pesos que lleva la misma.
*/
TreeList * addInOrder(TreeList *list, Btree * node) ;

/*
    joinTrees: Btree* Btree* -> Btree

    Devuelve un nuevo Btree en donde los hijos (izq y der) apuntan
    a los nodos dados.
*/
Btree *joinTrees(Btree *left, Btree *right) ;

/*
    filterZero: Tuple* -> TreeList

    A partir de un array de Tuples crea una TreeList con los las tuplas
    que tengan frecuencia mayor a 0.
*/
TreeList * filterZero(Tuple *A) ;

/*
    createHuffmanTree: TreeList* -> Btree*

    Crea un arbol de codificacion de Huffman a partir de una TreeList.
*/
Btree * createHuffmanTree(TreeList *treeList) ;

void printBtree(Btree *tree);

/*
    getLettersCode: Btree* char* table* [] len -> void

    Dado un arbol de Huffman lo recorre y llena una un array
    en cada letra con su codificacion correspondiente.
*/
void getLettersCode(Btree *tree, char *code, char *table[], int len) ;

/*
    encodeText: char* [], char*, len -> char*

    Dado un char* lo va recorriendo y devuelve un nuevo char* en donde
    se reemplaza cada letra por su codificacion correspondiente.
*/
char *encodeText(char *table[], char *text, int len) ;

/*
    encodeTree: Btree* char* char* int* int*

    Dado un arbol de Huffman lo va recorriendo y va llenando un char* con
    la informacion del arbol serializado.
*/
void encodeTree(Btree *tree, char *encodedTree, char *letters, int *lenTree, int *lenLetters);

/*
    achicatte: char* -> void

    Recive el nombre de un archivo para comprimir y crea
    un archivo nuevo con el archivo codificado y otro con
    el arbol de Huffman codificado.
*/
void achicatte(char * path);

#endif