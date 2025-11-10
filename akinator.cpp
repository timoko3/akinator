#include "akinator.h"

#include "general/poison.h"

#include "protectionAkinator.h"

#include "general/debug.h"


#include <assert.h>
#include <stdio.h>
#include <malloc.h>

static void freeNode(treeNode_t* node);
static curAnchorNode treeSortNodeInsert(treeNode_t* node, treeVal_t insertVal);

curAnchorNode akinatorCtor(akinator_t* tree){
    assert(tree);

    tree->size = 1;

    tree->root = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    assert(tree->root);

    tree->root->data = TREE_POISON;
    tree->root->left = NULL;
    tree->root->right = NULL;

    return tree->root;
}

curAnchorNode treeDtor(akinator_t* tree){
    assert(tree);

    freeNode(tree->root);

    poisonMemory(&tree->size, sizeof(tree->size));

    return NULL;
}

curAnchorNode treeSortInsert(akinator_t* tree, treeVal_t insertVal){
    assert(tree);

    log(tree, "before", "insert", insertVal);

    curAnchorNode insertionAddr = treeSortNodeInsert(tree->root, insertVal);

    LPRINTF("insertionAddr: %p", insertionAddr);

    (tree->size)++;

    log(tree, "after", "insert", insertVal);

    return insertionAddr;
}

void printPreOrder(const treeNode_t* node){
    assert(node);

    printf("(");
    printf("%d", node->data);

    if(node->left){
        printPreOrder(node->left);
    }
    if(node->right){
        printPreOrder(node->right);
    }

    printf(")");
}

void printInOrder(const treeNode_t* node){
    assert(node);

    if(node->left){
        printInOrder(node->left);
    }

    printf("(");
    printf("%d", node->data);

    

    if(node->right){
        printInOrder(node->right);
    }

    printf(")");
}


void printPostOrder(const treeNode_t* node){
    assert(node);

    if(node->left){
        printPostOrder(node->left);
    }
    if(node->right){
        printPostOrder(node->right);
    }
    printf("(");
    printf("%d", node->data);

    printf(")");
}

static void freeNode(treeNode_t* node){
    assert(node);
    
    if(node->left){
        freeNode(node->left);
    }

    if(node->right){
        freeNode(node->right);
    }

    poisonMemory(node, sizeof(*node));
    free(node);
    node = NULL;
}

static curAnchorNode treeSortNodeInsert(treeNode_t* node, treeVal_t insertVal){
    assert(node);

    curAnchorNode result = NULL;

    bool toPut = false;
    bool putLeft = false;

    if(insertVal <= node->data){
        if(node->left){
            treeSortNodeInsert(node->left, insertVal);
        }
        else{
            toPut = true;
            putLeft = true;
        }
        
    }
    else{
        if(node->right){
            treeSortNodeInsert(node->right, insertVal);
        }
        else{
            toPut = true;
        }
    }

    if(toPut){
        if(putLeft){
            node->left = (treeNode_t*) calloc(1, sizeof(treeNode_t));
            node->left->data  = insertVal;
            node->left->left  = NULL;
            node->left->right = NULL;
            return node->left;
        }
        else{
            node->right = (treeNode_t*) calloc(1, sizeof(treeNode_t));
            node->right->data  = insertVal;
            node->right->left  = NULL;
            node->right->right = NULL;
            return node->right;
        }
    }

    return result;
}

