#ifndef __COMPRESOR_IO_
#define __COMPRESOR_IO_
#include "resources.h"

void computeFrequency (Tuple *A, char *text, int len) ;

void sortTuples(Tuple *A, int len) ;

TreeList * addInOrder(TreeList *list, Btree * node) ;

Btree *joinTrees(Btree *left, Btree *right) ;

TreeList * filterZero(Tuple *A) ;

Btree * createHuffmanTree(TreeList *treeList) ;

void printBtree(Btree *tree) ;

void getLettersCode(Btree *tree, char *code, char *table[], int len) ;

char *encodeText(char *table[], char *text, int len) ;

void encodeTree(Btree *tree, char *encodedTree, char *letters, int *lenTree, int *lenLetters);

void achicatte(char * path);

#endif