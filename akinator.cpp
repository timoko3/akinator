#include "akinator.h"

#include "general/poison.h"
#include "general/debug.h"
#include "general/strFunc.h"
#include "protectionAkinator.h"
#include "akinatorUI.h"
#include "general/strFunc.h"

#include <assert.h>
#include <stdio.h>
#include <malloc.h>

static void freeNode(treeNode_t* node);
// static curAnchorNode treeSortNodeInsert(treeNode_t* node, treeVal_t insertVal);

curAnchorNode akinatorCtor(akinator_t* akinator){
    assert(akinator);

    akinator->size = 1;

    akinator->root = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    assert(akinator->root);

    akinator->root->data = "someThing";
    akinator->root->left = NULL;
    akinator->root->right = NULL;

    akinator->curState.Node = akinator->root;

    return akinator->root;
}

curAnchorNode akinatorDtor(akinator_t* akinator){
    assert(akinator);

    freeNode(akinator->root);

    poisonMemory(&akinator->size, sizeof(akinator->size));

    return NULL;
}

curAnchorNode akinatorGuess(akinator_t* akinator){
    assert(akinator);

    log(akinator, "before guess");

    while(true){
        askQuestionUser(akinator);
        char* answer = getAnswerUser(akinator);
        if(isYes(answer)){
            if(!(*curNode(akinator))->left){
                printResult(akinator);
                free(answer);
                break;
            }
            *curNode(akinator) = (*curNode(akinator))->left;
        }
        else if(isNo(answer)){
            if(!(*curNode(akinator))->right){
                // askIntended();
                free(answer);
                break;
            }
            *curNode(akinator) = (*curNode(akinator))->right;
        }
        log(akinator, "during guess");
    }

    log(akinator, "after guess");

    return *curNode(akinator);
}

curAnchorNode akinatorSaveAndExit(akinator_t* akinator){
    assert(akinator);

    return NULL;
}


// curAnchorNode treeSortInsert(akinator_t* tree, treeVal_t insertVal){
//     assert(tree);

//     log(tree, "before", "insert", insertVal);

//     curAnchorNode insertionAddr = treeSortNodeInsert(tree->root, insertVal);

//     LPRINTF("insertionAddr: %p", insertionAddr);

//     (tree->size)++;

//     log(tree, "after", "insert", insertVal);

//     return insertionAddr;
// }

void printPreOrder(const treeNode_t* node){
    assert(node);

    printf("(");
    printf("%s", node->data);

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
    printf("%s", node->data);

    

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
    printf("%s", node->data);

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

// static curAnchorNode treeSortNodeInsert(treeNode_t* node, treeVal_t insertVal){
//     assert(node);

//     curAnchorNode result = NULL;

//     bool toPut = false;
//     bool putLeft = false;

//     if(insertVal <= node->data){
//         if(node->left){
//             treeSortNodeInsert(node->left, insertVal);
//         }
//         else{
//             toPut = true;
//             putLeft = true;
//         }
        
//     }
//     else{
//         if(node->right){
//             treeSortNodeInsert(node->right, insertVal);
//         }
//         else{
//             toPut = true;
//         }
//     }

//     if(toPut){
//         if(putLeft){
//             node->left = (treeNode_t*) calloc(1, sizeof(treeNode_t));
//             node->left->data  = insertVal;
//             node->left->left  = NULL;
//             node->left->right = NULL;
//             return node->left;
//         }
//         else{
//             node->right = (treeNode_t*) calloc(1, sizeof(treeNode_t));
//             node->right->data  = insertVal;
//             node->right->left  = NULL;
//             node->right->right = NULL;
//             return node->right;
//         }
//     }

//     return result;
// }

