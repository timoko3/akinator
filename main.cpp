#include "generalAkinator.h"
#include "protectionAkinator.h"

#include "string.h"

#include "malloc.h"

int main(void){
    akinator_t akinator;

    akinator.root = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    printf("Выделенная память: %d\n", malloc_usable_size(akinator.root));
    akinator.root->left = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    printf("Выделенная память: %d\n", malloc_usable_size(akinator.root->left));
    akinator.root->right = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    printf("Выделенная память: %d\n", malloc_usable_size(akinator.root->right));
    
    strcpy(akinator.root->data, "Привет?");
    strcpy(akinator.root->left->data, "Как дела?");
    strcpy(akinator.root->right->data, "Где ты?");
    akinator.root->left->left = NULL;
    akinator.root->left->right = NULL;
    akinator.root->right->left = NULL;
    akinator.root->right->right = NULL;

    log(&akinator, "test");
    // treeGraphDump(&akinator);
    // treeGraphDump(&akinator);
    
    
    free(akinator.root->left);
    free(akinator.root->right);
    free(akinator.root);
}