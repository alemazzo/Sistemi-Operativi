
#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct node
{
    int key;
    double x;
    struct node *left;
    struct node *right;

} NODE;

void deallocate_tree(NODE **root)
{
    if (*root == NULL)
        return;

    deallocate_tree(&((*root)->left));
    deallocate_tree(&((*root)->right));
    free(*root);
    *root = NULL;
}

void deallocate_tree(NODE *node)
{
    // node = 1234 -> {primo nodo}
    // &node = 9876
    if (node == NULL)
        return;

    deallocate_tree(node->left);
    deallocate_tree(node->right);
    free(node);
    node = NULL;
}

void tree_create(NODE **root) {}

void ciao(int n)
{
    n = 100;
}
void ciao2(int **n)
{
    n = 54321;
    // print(*n) -> 12345678
    *n = NULL;
}

int main()
{

    // 54321
    int *arrivederci = malloc(sizeof(int)); // 12345678
    ciao2(arrivederci);
    // print(arrivederci)

    ciao2(&arrivederci);
    // print(arrivederci)

    // 5678
    NODE *root;
    // root = 1234 -> {primo nodo}
    // &root = 5678 -> root: 1234 -> {primo nodo}
    tree_create(root);

    deallocate_tree(root);
}
