#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "resources.h"
#include "io.h"

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
    if(tree->left == NULL && tree->right == NULL) (*index)++;
    for(;tree->left != NULL && tree->right != NULL; (*index)++) {
        if(encodedFileText[(*index)] == '0') tree = tree->left;
        else tree = tree->right;
    }
    return tree->letter;
}

void decompresor(char *encodedTextPath, char *encodedTreePath, char *outputPath) {
    int encodedTextLen = 0, encodedTreeLen = 0, enterPosition = 0, nlen = 0;

    char *encodedFileText2 = readfile(encodedTextPath, &encodedTextLen);
    if (encodedTextLen == 0) {
        printf("ERROR: el archivo .hf esta vacio.\n");
        return;
    }
    char *encodedFileText = explode(encodedFileText2, encodedTextLen ,&nlen);
    free(encodedFileText2);

    char *encodedTree = readfile(encodedTreePath, &encodedTreeLen);
    if (encodedTreeLen == 0) {
        printf("ERROR: el archivo .tree esta vacio.\n");
        return;
    }
    
    for (int i = 0; i < encodedTreeLen; i++) {
        if (encodedTree[i] == '\n') {
            enterPosition = i;
            break;
        }
    }

    int treeIndex = 0, letterPosition = 0;

    Btree *tree = readTree(encodedTree, &treeIndex, enterPosition, &letterPosition);
    free(encodedTree);

    char *decodedText = malloc(sizeof(char)*1024);
    int textIndex = 0, textSize = 1, i=0;

    for(i = 0; textIndex < nlen; i++){// crea el texto desencodeado
        if(i >= textSize * 1024){ 
            textSize++;
            decodedText = realloc(decodedText, textSize* 1024);
        }
        decodedText[i] = buildText(tree, encodedFileText, &textIndex);
    }
    free(encodedFileText);

    destroyBtree(tree);

    writefile(outputPath, decodedText, i);

    free(decodedText);
}