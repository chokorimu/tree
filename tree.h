#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int value;
    struct node* left;
    struct node* right;
};

struct node** searchNode(struct node** root, int value);
bool isNumberExist(struct node** root, int value);
void insertNode(struct node** root, int newValue);
void deleteNode(struct node** root, int value);
void printInOrder(struct node** root);

#endif
