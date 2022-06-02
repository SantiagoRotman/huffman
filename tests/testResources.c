#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../io.h"
#include "../resources.h"

void testCreateTuple() {
    Tuple *A = createTuple();
    for (int i = 0; i < 256; i++){
        assert(A[(unsigned char)i].data == (char)i);
        assert(A[(unsigned char)i].index == 0);
    }
}

void testCreateTreeNode() {
    Btree *tree = createTreeNode('z',4);
    assert(tree != NULL);
    assert(tree->letter == 'z');
    assert(tree->weight == 4);
    assert(tree->left == NULL);
    assert(tree->right == NULL);
}

int main() {
    testCreateTuple();
    testCreateTreeNode();
    printf("Todos los test han sido ejecutados y sin errores.\n");
    return 0;
}