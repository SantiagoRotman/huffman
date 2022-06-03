#ifndef __RESOURCES_IO_
#define __RESOURCES_IO_

#define MAX_LETTERS 256

/*
  Estructura que tiene una letra y un indice que indica
  la frecuencia de aparicion de la letra en el texto.
*/
typedef struct tuple {
  char data;
  int frequency;
} Tuple;

/*
  Estructura que representa un nodo de un arbol binario.
  Cada nodo contiene una letra y el peso de la letra y el peso.
  Ademas tiene 2 punteros a sus nodos hijos (izq y der).
*/
typedef struct Tnode {
    char letter;
    int weight;
    struct Tnode *left, *right;
} Btree;

/*
  Lista enlazada de arboles.
  Contiene un arbol como dato y un puntero al sig elemento de la lista.
*/
typedef struct node {
    Btree *tree;
    struct node *sig;
} TreeList;

/*
  createTuple: () -> Tuple
  Devuelve un puntero a un array de (MAX_LETTERS) cantidad de Tuples.
*/
Tuple *createTuple() ;

/*
  printTuples: Tuple* int-> void
  Si toFile es 1 lo imprime a un archivo para que se pueda ver mejor que en la consola
  Imprime los datos de un array de Tuples.
*/
void printTuples(Tuple *A,  int toFile) ;

/*
  printTreeList: TreeList* int-> void
  Si toFile es 1 lo imprime a un archivo para que se pueda ver mejor que en la consola
  Imprime los datos de los elementos de un array de arboles.
*/
void printTreeList(TreeList *A,  int toFile) ;

/*
  destroyBtree: Btree* -> void
  Libera la memoria de los nodos de un arbol.
*/
void destroyBtree(Btree *tree);

/*
  printBtree: Btree* -> void
  Lee un Btree* y lo imprime por pantalla (preorden).
*/
void printBtree(Btree *tree);

/*
  createTreeNode: char int -> Btree*
  Devuelve un Btree* que tiene como datos el char y el int pasados
  en los parametros.
*/
Btree *createTreeNode(char c, int i);

#endif
