#include <stdlib.h>
#include <stdio.h>
#include "resources.h"

Tuple * createTuple() {
    Tuple *A = malloc(sizeof(Tuple)*MAX_LETTERS);
    for(int i = 0; i < MAX_LETTERS; i++) {
        A[i].data = (char)i;
        A[i].index = 0; 
    }
    return A;
}

void printTuples(Tuple *A) {
    for(int i = 0; i < MAX_LETTERS; i++) {
        printf("%c-", A[i].data);
        printf("%d", A[i].index);  
        printf("\n");
    }
}

void printTreeList(TreeList *A) {
    TreeList *aux = A;
    for(;aux != NULL; aux=aux->sig) {
        printf("%c-", aux->tree->letter);
        printf("%d", aux->tree->weight);
        printf("\n");
    }
}
void destroyBtree(Btree * tree) {
    if(tree->left != NULL)  destroyBtree(tree->left);
    if(tree->right != NULL) destroyBtree(tree->right);
    free(tree);
}

Btree *createTreeNode (char c, int i) {
    Btree *node = malloc(sizeof(Btree));
    node->letter = c;
    node->weight = i;
    node->left = NULL;
    node->right = NULL;
    return node;
}

