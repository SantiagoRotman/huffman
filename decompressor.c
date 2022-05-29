#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compresor.c"

// typedef struct Tnode {
//     char letter;
//     int weight;
//     struct Tnode *left, *right;
// } Btree;

// typedef struct node {
//     Btree * tree;
//     struct node *sig;
// } TreeList;

// Btree *joinTrees(Btree *left, Btree *right) {
//     Btree *new = malloc(sizeof(Btree));
//     new->letter = ' ';
//     new->weight = left->weight + right->weight;
//     new->left = left;
//     new->right = right;
//     return new;
// }

Btree *readTree(char *encodedTree, int *treeIndex, int enterPosition, int *letterIndex) {
    Btree *buff = NULL;
    if (encodedTree[*treeIndex] == '0') {
        buff = malloc(sizeof(Btree));
        buff->letter = ' ';
        buff->weight = 0;
        (*treeIndex)++;
        buff->left = joinTrees(readTree(encodedTree, treeIndex, enterPosition, letterIndex), buff);
        (*treeIndex)++;
        buff->right = joinTrees(readTree(encodedTree, treeIndex, enterPosition, letterIndex), buff);
    }
    else{
        buff = malloc(sizeof(Btree));
        (*letterIndex)++;
        printf("____%c____", encodedTree[(*letterIndex) + enterPosition]);
        buff->letter = encodedTree[(*letterIndex) + enterPosition];
        buff->weight = 0;
        buff->left = NULL;
        buff->right = NULL;
    }
    return buff;
}

char buildText(Btree *tree, char *encodedFileText, int *index) {
    if (tree->left == NULL && tree->right == NULL){
        printf("->%c", tree->letter);
        return tree->letter;
    }


    (*index)++; 
    printf("%c", encodedFileText[(*index)-1]);
    if(encodedFileText[(*index)-1] == '0') buildText(tree->left , encodedFileText, index);
    else  buildText(tree->right, encodedFileText, index);

}

int decompresor(char * encodedTextPath, char * encodedTreePath) {
    int encodedTextLen = 0, encodedTreeLen = 0, enterPosition = 0, nlen = 0;

    char *encodedFileText = readfile(encodedTextPath, &encodedTextLen);
    encodedFileText = explode(encodedFileText, encodedTextLen ,&nlen);


    char *encodedTree = readfile(encodedTreePath, &encodedTreeLen);
    printf("%s\n", encodedTree);

    for (int i = 0; i < encodedTreeLen; i++) {
        if (encodedTree[i] == '\n') {
            enterPosition = i;
            break;
        }
    }
    printf("-------------->%d\n", enterPosition);
    int treeIndex = 0, letterPosition = 0;

    printf("-1-\n");
    Btree *tree = readTree(encodedTree, &treeIndex, enterPosition, &letterPosition);
    printf("-2-\n");


    char *decodedText = malloc(sizeof(char));
    decodedText[0]='\0';
    int textIndex = 0, textSize = 0;
    printf("-3-\n");
    printf("%s\n", encodedFileText);
    while(textIndex <= 250){
        char aux = buildText(tree, encodedFileText, &textIndex);
        printf("\n->%c<-", aux);
    }

    printf("%s\n", decodedText);

    return 0;
}