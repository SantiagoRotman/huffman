#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "resources.h"

void computeFrequency (Tuple *A, char *text, int len) {
    for(int i = 0; i < len; i++) {
        A[(unsigned char)text[i]].index ++;
    }
}

void sortTuples(Tuple *A, int len) {
    int i, j;
    Tuple aux;
    for (i = 1; i < len; i++) {
        aux = A[i];
        j = i - 1;

        while (j >= 0 && A[j].index < aux.index) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = aux;
    }
}


TreeList * addInOrder(TreeList *list, Btree * node) {
    TreeList *new = malloc(sizeof(TreeList));
    if (list == NULL) {
        new->tree = node;
        new->sig = NULL;
        return new;
    }
    
    if(list->tree->weight >= node->weight) {
        new->tree = node;
        new->sig = list;
        return new;
    }

    TreeList *aux = list;
    for (; aux->sig != NULL && aux->sig->tree->weight < node->weight ; aux = aux->sig);
    new->tree = node;
    new->sig = aux->sig;
    aux->sig = new;
    return list;
}

Btree *joinTrees(Btree *left, Btree *right) {
    Btree *new = malloc(sizeof(Btree));
    new->letter = ' ';
    new->weight = left->weight + right->weight;
    new->left = left;
    new->right = right;
    return new;
}

TreeList * filterZero(Tuple *A) { //pensar el nombre pq no solo filtta los 0 sino que crea la TreeList
    int i = 0;
    TreeList *list = NULL;
    for (i = 0; i < MAX_LETTERS && A[i].index != 0; i++) {
        if (A[i].index != 0) {
            Btree *node = createTreeNode(A[i].data, A[i].index);
            list = addInOrder(list, node);
        }
    }

    //printTreeList(list, 1);
    return list;
}

Btree * createHuffmanTree(TreeList *treeList) {
    TreeList *aux;
    Btree *buff = NULL;
    while (treeList->sig != NULL && treeList != NULL) {
        aux = treeList;
        buff = joinTrees(treeList->tree,treeList->sig->tree);
        treeList = treeList->sig->sig;
        free(aux->sig);
        free(aux);
        treeList = addInOrder(treeList, buff);
    }
    Btree *new = treeList->tree;
    free(treeList);
    return new;
}

void printBtree(Btree *tree) {
    if(tree->left != NULL)  printBtree(tree->left);
    //printf("%c - %d\n", tree->letter, tree->weight);
    if(tree->right != NULL) printBtree(tree->right);
    // if (tree->right == NULL && tree->left == NULL)  printf("%c - %d", tree->letter, tree->weight);
}

// void codificar(Btree *tree, char * codifcacion, char *tabla[]) {
//     if(tree->left != NULL) {
//         char B[80];
//         strcpy(B, codifcacion);
//         codificar(tree->left, strcat(B, "0"), tabla);
//         }
//     if(tree->right != NULL) {
//         char B[80];
//         strcpy(B, codifcacion);
//         codificar(tree->right, strcat(B, "1"), tabla);
//         }
//     if (tree->right == NULL && tree->left == NULL) {
//         tabla[(unsigned char)tree->letter] = malloc(sizeof(char)*strlen(codifcacion));
//         strcpy(tabla[(unsigned char)tree->letter], codifcacion);
//         printf("%s-----%c\n", tabla[(unsigned char) tree->letter], tree->letter);
//     }
// }

void getLettersCode(Btree *tree, char *code, char *table[], int len) {

    if(tree->left != NULL) {
        code[(len)] = '0';
        getLettersCode(tree->left, code, table, len+1);
    }
    if(tree->right != NULL) {
        
        code[(len)] = '1';
        getLettersCode(tree->right, code, table, len+1);
    }
    if (tree->right == NULL && tree->left == NULL) {
        if(len == 0){
            table[(unsigned char)tree->letter] = malloc(sizeof(char)+1);
            strcpy(table[(unsigned char)tree->letter], "1");
        }
        else{
            code[(len)] = '\0';
            table[(unsigned char)tree->letter] = malloc(sizeof(char)*strlen(code)+1);
            strcpy(table[(unsigned char)tree->letter], code);
        }
        
    }
}

char *encodeText(char *table[], char *text, int len) {
    int j = 0, ban = 2, index = 0;
    char *output = NULL;
    output = realloc(output, (sizeof(char)*1024));
    output[0] = '\0';
    for(int i = 0; i < len ; i++ ){
        char c = text[i];
        int lenCode = strlen(table[(unsigned char)c]);
        if(lenCode+j >= 1024){
            ban++;
            output = realloc(output, (sizeof(char)*ban*1024));
            j = 0;
        }
        j = j + lenCode;
        
        strcpy(output + index, table[(unsigned char)c]);
        index = index + lenCode;
    }
    output[index]= '\0';
    return output;
}


void encodeTree(Btree *tree, char *encodedTree, char *letters, int *lenTree, int *lenLetters){
    if (tree->right == NULL && tree->left == NULL) {
        encodedTree[(*lenTree)] = '1';
        letters[(*lenLetters)] = tree->letter;
        (*lenLetters)++;
        (*lenTree)++;
    }
    else{
        encodedTree[(*lenTree)] = '0';
        (*lenTree)++;
    }

    if(tree->left != NULL)  encodeTree(tree->left, encodedTree, letters, lenTree, lenLetters );
    if(tree->right != NULL) encodeTree(tree->right, encodedTree, letters, lenTree, lenLetters );
}


void achicatte(char * path){
    int len = 0;
    char *fileText = readfile(path, &len);

    Tuple *letterFrequency = createTuple();
    computeFrequency(letterFrequency, fileText, len);
    

    TreeList *treeList =  NULL;
    sortTuples(letterFrequency, 256);
    treeList = filterZero(letterFrequency);
    //printTuples(letterFrequency, 0);
    
    Btree *tree = createHuffmanTree(treeList);
    free(letterFrequency);
    //free(treeList);

    char * A[256];
    for(int i = 0; i < 256; i++) A[i]=NULL;
    printf("dddddddddddddddddd\n");
    char code[300] = "";
    getLettersCode(tree, code, (char **)A, 0);
    //for(int i = 0; i <= MAX_LETTERS; i++) if (A[i]!= NULL) printf("%s\n", A[i]);
    printf("ccccccccccccccc\n");
    char encodedTree[10000]="", letters[257]="";
    int lenTree = 0, lenLetters = 0;
    encodeTree(tree, encodedTree, letters, &lenTree, &lenLetters);

    destroyBtree(tree);
    printf("bbbbbbbbbbbbbb\n");
    encodedTree[lenTree] = '\0';

    printf("aaaaaaaaaa\n");
    int nTreeLen = lenTree + lenLetters+1, nlen = 0;
    char *nTree = malloc(sizeof(char)*(lenTree + lenLetters + 3));
    strcpy(nTree, encodedTree);
    nTree[lenTree] = '\n';
    //strncpy(nTree+lenTree+1, letters, lenLetters);
    for(int i = 0; i < lenLetters; i++) nTree[lenTree+1+i] = letters[i];
    nTree[lenTree + lenLetters + 2]  = '\0';
    printf("1\n");
    char * encodedText2 = encodeText(A, fileText, len);
    printf("2\n");
    printf("%s -- %d\n",encodedText2, strlen(encodedText2));
    char * encodedText = implode(encodedText2, strlen(encodedText2) , &nlen);
    printf("3\n");
    free(encodedText2);
    printf("4\n");

    for(int i = 0; i< 256; i++){
        if(A[i]!=NULL) {
            printf("%s\n", A[i]);
            free(A[i]);
        }
    }
    printf("5\n");

    char hfPath[100];
    strcat(strcpy(hfPath, path), ".hf");
    char treePath[100]; 
    strcat(strcpy(treePath, path), ".tree");
    writefile(hfPath, encodedText, nlen);
    writefile(treePath, nTree, nTreeLen);
    free(nTree);
    free(fileText);
    free(encodedText);

}