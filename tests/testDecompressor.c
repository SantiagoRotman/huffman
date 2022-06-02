#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../io.h"
#include "../resources.h"
#include "../decompressor.h"

void testReadTree() {
    char *encodedTree = "00111\nabc";
    int treeIndex = 0, enterPosition = 5, letterIndex = 0;
    Btree *tree = readTree(encodedTree, &treeIndex, enterPosition, &letterIndex);
    assert(tree != NULL);
    assert(tree->letter == ' ');
    assert(tree->weight == 0);
    assert(tree->left->left->letter == 'a');
    assert(tree->left->right->letter == 'b');
    assert(tree->right->letter == 'c');
}

void testBuildText() {
    char *encodedTree = "00111\nabc", *encodedFileText = "00011";
    int treeIndex = 0, enterPosition = 5, letterIndex = 0, textIndex = 0, textSize = 1;
    Btree *tree = readTree(encodedTree, &treeIndex, enterPosition, &letterIndex);
    char *decodedText = malloc(sizeof(char)*1024);
    int i = 0;
    for(; textIndex < 5; i++){
        if(i >= textSize * 1024){
            textSize++;
            decodedText = realloc(decodedText, textSize* 1024);
        }
        decodedText[i] = buildText(tree, encodedFileText, &textIndex);
    }
    decodedText = realloc(decodedText, sizeof(char)*(textSize+1)*1024);
    decodedText[i] = '\0';
    assert(!strcmp(decodedText, "abc"));
}

int main() {
    testReadTree();
    testBuildText();
    printf("Todos los test han sido ejecutados y sin errores.\n");
    return 0;
}
