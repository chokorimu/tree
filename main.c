#include "tree.h"

int main() {
    struct node* root = NULL;
    
    insertNode(&root, 40);
    insertNode(&root, 20);
    insertNode(&root, 10);
    insertNode(&root, 30);
    insertNode(&root, 50);
    insertNode(&root, 60);

    printInOrder(&root);
    printf("\n%d\n", isNumberExist(&root, 50));

    deleteNode(&root, 50);

    printInOrder(&root);
    printf("\n%d\n", isNumberExist(&root, 50));

    return 0;
}