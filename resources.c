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

void printTuples(Tuple *A,  int toFile) {
    if(toFile){
        FILE * f=  fopen("exit", "w");
        for(int i = 0; i < MAX_LETTERS; i++) {
            fprintf(f,"%c-", A[i].data);
            fprintf(f,"%d", A[i].index);
            fprintf(f,"\n");
        }
        fclose(f);
    }

    else {
        for(int i = 0; i < MAX_LETTERS; i++) {
            printf("%c-", A[i].data);
            printf("%d", A[i].index);
            printf("\n");
        }
    }
}

void printTreeList(TreeList *A,  int toFile) {
    TreeList *aux = A;
    if(toFile){
        FILE * f=  fopen("exit2", "w");
        for(;aux != NULL; aux=aux->sig) {
            fprintf(f,"%c-", aux->tree->letter);
            fprintf(f,"%d", aux->tree->weight);
            fprintf(f,"\n");

        }
        fclose(f);
    }
    else{
        for(;aux != NULL; aux=aux->sig) {
            printf("%c-", aux->tree->letter);
            printf("%d", aux->tree->weight);
            printf("\n");
        }
    }
}

void printBtree(Btree *tree) {
    if(tree->left != NULL)  printBtree(tree->left);
    //printf("%c - %d\n", tree->letter, tree->weight);
    if(tree->right != NULL) printBtree(tree->right);
    // if (tree->right == NULL && tree->left == NULL)  printf("%c - %d", tree->letter, tree->weight);
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

