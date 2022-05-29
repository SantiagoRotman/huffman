#ifndef __RESOURCES_IO_
#define __RESOURCES_IO_

#define MAX_LETTERS 256

typedef struct tuple {
  char data;
  int index;
} Tuple;

typedef struct Tnode {
    char letter;
    int weight;
    struct Tnode *left, *right;
} Btree;

typedef struct node {
    Btree * tree;
    struct node *sig;
} TreeList;

Tuple * createTuple() ;

void printTuples(Tuple *A) ;

void printTreeList(TreeList *A) ;

void destroyBtree(Btree * tree);

Btree *createTreeNode (char c, int i);

#endif
