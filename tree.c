#include "tree.h"

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

void deleteNode(struct node** root, int value) {
    struct node** targetLink = searchNode(root, value);
    if (*targetLink == NULL) {
        return;
    }
    struct node* nodeToDelete = *targetLink;
    if (nodeToDelete->left != NULL && nodeToDelete->right != NULL) {
        struct node* maxLeft = nodeToDelete->left;
        while (maxLeft->right != NULL) {
            maxLeft = maxLeft->right;
        }
        maxLeft->right = nodeToDelete->right;
        
        *targetLink = nodeToDelete->left;
    } 
    else {
        if (nodeToDelete->left == NULL) {
            *targetLink = nodeToDelete->right;
        } else {
            *targetLink = nodeToDelete->left;
        }
    }
    free(nodeToDelete);
}

void printInOrder(struct node** root) {
    if ((*root) == NULL) {
        return;
    }
    printInOrder(&((*root)->left));
    printf("%d, ", (*root)->value);
    printInOrder(&((*root)->right));
}
