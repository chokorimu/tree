#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int value;
    bool isLeaf;
    struct node* left;
    struct node* right;
};

void allocate(struct node** root, int value) {
    struct node* newNode = malloc(sizeof(*root));
    newNode->value = value;
    newNode->isLeaf = true;
    newNode->left = NULL;
    newNode->right = NULL;

    if(*root == NULL) {
        *root = newNode;
        return;
    }
    struct node* cursor = *root;
    while(!cursor->isLeaf || cursor->right == NULL) {
        if(cursor)
        cursor->right = newNode;
        return;
    }
    cursor->left = newNode;
}

int main() {
    struct node* root = NULL;
    allocate(&root, 5);
    return 0;
}