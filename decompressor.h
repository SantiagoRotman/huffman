#ifndef __DECOMPRESSOR_IO_
#define __DECOMPRESSOR_IO_
#include "resources.h"

Btree *readTree(char *encodedTree, int *treeIndex, int enterPosition, int *letterIndex) ;

char buildText(Btree *tree, char *encodedFileText, int *index) ;

int decompresor(char * encodedTextPath, char * encodedTreePath, char * outputPath) ;

#endif