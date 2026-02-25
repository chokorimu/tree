#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int value;
    struct node* left;
    struct node* right;
};

void insertNode(struct node** root, int newValue) {
    struct node* newNode = malloc(sizeof(*newNode));
    newNode->value = newValue;
    newNode->left = NULL;
    newNode->right = NULL;

    if(*root == NULL) {
        *root = newNode;
        return;
    }
    struct node* cursor = *root;
    while(true) {
        if(newValue == cursor->value) {
            free(newNode);
            return;
        }
        if(newValue < cursor->value) {
            if(cursor->left == NULL) { 
                cursor->left = newNode;      
                return;
            } cursor=cursor->left;
        }
        else if(newValue > cursor->value) {
            if(cursor->right == NULL) { 
                cursor->right = newNode;
                return;      
            } cursor=cursor->right;
        }
    }
}

int main() {
    struct node* root = NULL;
    insertNode(&root, 5);
    insertNode(&root, 6);
    insertNode(&root, 6);
    return 0;
}