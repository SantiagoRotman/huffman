#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "resources.h"
#include "io.h"

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
        buff->left = readTree(encodedTree, treeIndex, enterPosition, letterIndex);
        (*treeIndex)++;
        buff->right = readTree(encodedTree, treeIndex, enterPosition, letterIndex);
    }
    else{
        buff = malloc(sizeof(Btree));
        (*letterIndex)++;
        buff->letter = encodedTree[(*letterIndex) + enterPosition];
        buff->weight = 0;
        buff->left = NULL;
        buff->right = NULL;
    }
    return buff;
}

char buildText(Btree *tree, char *encodedFileText, int *index) {
    if (tree->left == NULL && tree->right == NULL) return tree->letter;

    (*index)++; 
    if(encodedFileText[(*index)-1] == '0') buildText(tree->left , encodedFileText, index);
    else  buildText(tree->right, encodedFileText, index);

}

int decompresor(char * encodedTextPath, char * encodedTreePath) {
    int encodedTextLen = 0, encodedTreeLen = 0, enterPosition = 0, nlen = 0;

    char *encodedFileText = readfile(encodedTextPath, &encodedTextLen);
    encodedFileText = explode(encodedFileText, encodedTextLen ,&nlen);


    char *encodedTree = readfile(encodedTreePath, &encodedTreeLen);
    

    for (int i = 0; i < encodedTreeLen; i++) {
        if (encodedTree[i] == '\n') {
            enterPosition = i;
            break;
        }
    }

    int treeIndex = 0, letterPosition = 0;

    Btree *tree = readTree(encodedTree, &treeIndex, enterPosition, &letterPosition);


    char *decodedText = malloc(sizeof(char)*1024);
    int textIndex = 0, textSize = 1;
    printf("\n\n\n\n");
    for(int i = 0;textIndex < nlen; i++){
        if(i >= textSize * 1024)  decodedText = realloc(decodedText, (textSize++)* 1024);
        decodedText[i] = buildText(tree, encodedFileText, &textIndex);
    }

    printf("%s\n", decodedText);

    return 0;
}