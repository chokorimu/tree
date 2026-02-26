#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int value;
    struct node* left;
    struct node* right;
};

struct node** searchNode(struct node** root, int value) {
    struct node** cursor = root;
    while (*cursor != NULL) {
        if (value == (*cursor)->value) {
            return cursor;
        }
        if (value < (*cursor)->value) {
            cursor = &((*cursor)->left); 
        } else {
            cursor = &((*cursor)->right);
        }
    }
    return cursor; 
}

bool isNumberExist(struct node** root, int value) {
    return *searchNode(root, value) != NULL;
}

void insertNode(struct node** root, int newValue) {
    struct node** leaf = searchNode(root, newValue);
    if (*leaf != NULL) {
        return;
    }
    struct node* newNode = malloc(sizeof(struct node));
    newNode->value = newValue;
    newNode->left = NULL;
    newNode->right = NULL;

    *leaf = newNode; 
}

int main() {
    struct node* root = NULL;
    insertNode(&root, 40);
    insertNode(&root, 20);
    insertNode(&root, 10);
    insertNode(&root, 30);
    insertNode(&root, 50);
    insertNode(&root, 60);
    printf("%d\n", isNumberExist(&root, 50));
    return 0;
}