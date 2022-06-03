#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../io.h"
#include "../resources.h"
#include "../compressor.h"

void testComputeFrequency() {
    Tuple *A = createTuple();
    char *text = "blabla123";
    int len = 9;
    computeFrequency(A, text, len);
    assert(A['b'].frequency == 2);
    assert(A['l'].frequency == 2);
    assert(A['a'].frequency == 2);
    assert(A['1'].frequency == 1);
    assert(A['2'].frequency == 1);
    assert(A['3'].frequency == 1);
    free(A);
}

void testSortTuples() {
    Tuple *A = createTuple();
    A['a'].frequency = 1;
    A['b'].frequency = 2;
    A['c'].frequency = 3;
    sortTuples(A, 256);
    assert(A[0].data == 'c');
    assert(A[0].frequency == 3);
    assert(A[1].data == 'b');
    assert(A[1].frequency == 2);
    assert(A[2].data == 'a');
    assert(A[2].frequency == 1);
    assert(A[3].frequency == 0);
    free(A);
}

void testAddInOrder() {
    TreeList *treeList = malloc(sizeof(TreeList));
    Btree *tree = malloc(sizeof(Btree));
    tree->letter = 'a';
    tree->weight = 1;
    tree->right = NULL;
    tree->left = NULL;

    treeList->tree = tree;
    treeList->sig = NULL;

    Btree *nTree = malloc(sizeof(Btree));
    nTree->letter = 'b';
    nTree->weight = 5;
    nTree->right = NULL;
    nTree->left = NULL;

    Btree *nnTree = malloc(sizeof(Btree));
    nnTree->letter = 'c';
    nnTree->weight = 100;
    nnTree->right = NULL;
    nnTree->left = NULL;

    treeList = addInOrder(treeList, nTree);    
    treeList = addInOrder(treeList, nnTree);

    assert(treeList->tree == tree);
    assert(treeList->sig->tree == nTree);
    assert(treeList->sig->sig->tree == nnTree);
    free(treeList->sig->sig);
    free(treeList->sig);
    free(treeList);
    free(tree);
    free(nTree);
    free(nnTree);

}

void testJoinTrees() {
    Btree *tree = malloc(sizeof(Btree));
    tree->letter = 'a';
    tree->weight = 1;
    tree->right = NULL;
    tree->left = NULL;

    Btree *nTree = malloc(sizeof(Btree));
    nTree->letter = 'b';
    nTree->weight = 5;
    nTree->right = NULL;
    nTree->left = NULL;

    Btree *joined = joinTrees(tree, nTree);

    assert(joined->weight == 6);
    assert(joined->letter == ' ');
    assert(joined->left == tree);
    assert(joined->right == nTree);
    destroyBtree(joined);
}

void testCreateFilteredTreeList() {
    Tuple *A = createTuple();
    sortTuples(A, 256);
    TreeList *filtered = createFilteredTreeList(A);
    assert(filtered == NULL);
    free(filtered);
    
    Tuple *B = createTuple();
    B['a'].frequency = 1;
    sortTuples(B, 256);
    TreeList *filtered2 = createFilteredTreeList(B);

    assert(filtered2->sig == NULL);
    assert(filtered2->tree->weight == 1);
    assert(filtered2->tree->letter == 'a');
    free(filtered2->tree);
    free(filtered2);
    free(A);
    free(B);
}

void testCreateHuffmanTree() {
    Btree *tree = malloc(sizeof(Btree));
    tree->letter = 'a';
    tree->weight = 1;
    tree->right = NULL;
    tree->left = NULL;
    TreeList *treeList = malloc(sizeof(TreeList));
    treeList->tree = tree;
    treeList->sig = NULL;
    Btree *nTree = malloc(sizeof(Btree));
    nTree->letter = 'b';
    nTree->weight = 5;
    nTree->right = NULL;
    nTree->left = NULL;
    Btree *nnTree = malloc(sizeof(Btree));
    nnTree->letter = 'c';
    nnTree->weight = 100;
    nnTree->right = NULL;
    nnTree->left = NULL;

    treeList = addInOrder(treeList, nTree);    
    treeList = addInOrder(treeList, nnTree);

    Btree *Htree = createHuffmanTree(treeList);

    assert(Htree != NULL);
    assert(Htree->weight == 106);
    assert(Htree->letter == ' ');
    assert(Htree->left != NULL);
    assert(Htree->right != NULL);
    destroyBtree(Htree);

}

void testGetLettersCode() {
    Btree *tree = malloc(sizeof(Btree));
    tree->letter = 'a';
    tree->weight = 1;
    tree->right = NULL;
    tree->left = NULL;
    TreeList *treeList = malloc(sizeof(TreeList));
    treeList->tree = tree;
    treeList->sig = NULL;
    Btree *nTree = malloc(sizeof(Btree));
    nTree->letter = 'b';
    nTree->weight = 5;
    nTree->right = NULL;
    nTree->left = NULL;
    Btree *nnTree = malloc(sizeof(Btree));
    nnTree->letter = 'c';
    nnTree->weight = 100;
    nnTree->right = NULL;
    nnTree->left = NULL;

    treeList = addInOrder(treeList, nTree);    
    treeList = addInOrder(treeList, nnTree);

    Btree *Htree = createHuffmanTree(treeList);
    char code[300] = "", *A[256];
    for(int i = 0; i< 256; i++) A[i]=NULL;

    getLettersCode(Htree, code, A, 0);

    assert(!strcmp(A['a'], "00"));
    assert(!strcmp(A['b'], "01"));
    assert(!strcmp(A['c'], "1"));

    for(int i = 0; i< 256; i++){
        if(A[i]!=NULL) {
            free(A[i]);
        }
    }

    destroyBtree(Htree);

}

void testEncodeText() {
    Btree *tree = malloc(sizeof(Btree));
    tree->letter = 'a';
    tree->weight = 1;
    tree->right = NULL;
    tree->left = NULL;
    TreeList *treeList = malloc(sizeof(TreeList));
    treeList->tree = tree;
    treeList->sig = NULL;
    Btree *nTree = malloc(sizeof(Btree));
    nTree->letter = 'b';
    nTree->weight = 5;
    nTree->right = NULL;
    nTree->left = NULL;
    Btree *nnTree = malloc(sizeof(Btree));
    nnTree->letter = 'c';
    nnTree->weight = 100;
    nnTree->right = NULL;
    nnTree->left = NULL;

    treeList = addInOrder(treeList, nTree);    
    treeList = addInOrder(treeList, nnTree);

    Btree *Htree = createHuffmanTree(treeList);
    char code[300] = "", *A[256];
    for(int i = 0; i< 256; i++) A[i]=NULL;
    


    getLettersCode(Htree, code, A, 0);

    char *encodedText = encodeText(A, "abc", 3);

    assert(encodedText != NULL);
    assert(!strcmp(encodedText, "00011"));
    destroyBtree(Htree);
    free(encodedText);
    for(int i = 0; i< 256; i++){
        if(A[i]!=NULL) {
            free(A[i]);
        }
    }
}

void testEncodeTree() {
    Btree *tree = malloc(sizeof(Btree));
    tree->letter = 'a';
    tree->weight = 1;
    tree->right = NULL;
    tree->left = NULL;
    TreeList *treeList = malloc(sizeof(TreeList));
    treeList->tree = tree;
    treeList->sig = NULL;
    Btree *nTree = malloc(sizeof(Btree));
    nTree->letter = 'b';
    nTree->weight = 5;
    nTree->right = NULL;
    nTree->left = NULL;
    Btree *nnTree = malloc(sizeof(Btree));
    nnTree->letter = 'c';
    nnTree->weight = 100;
    nnTree->right = NULL;
    nnTree->left = NULL;

    treeList = addInOrder(treeList, nTree);    
    treeList = addInOrder(treeList, nnTree);

    Btree *Htree = createHuffmanTree(treeList);
    char encodedTree[1000]="", letters[256]="";
    int lenTree = 0, lenLetters = 0;

    encodeTree(Htree, encodedTree, letters, &lenLetters, &lenTree);
    assert(Htree != NULL);
    assert(!strcmp(encodedTree, "00111"));
    destroyBtree(Htree);


}

int main() {
    testComputeFrequency();
    testSortTuples();
    testAddInOrder();
    testJoinTrees();
    testCreateFilteredTreeList();
    testCreateHuffmanTree();
    testGetLettersCode();
    testEncodeText();
    testEncodeTree();
    printf("Todos los test han sido ejecutados y sin errores.\n");
    return 0;
}