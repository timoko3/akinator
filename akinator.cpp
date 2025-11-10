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
#include <string.h>

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
                char* intended = getIntended(akinator);
                akinatorInsertLeft(akinator, (*curNode(akinator)), intended);

                char* difference = getDifference(akinator, intended);
                akinatorInsertRight(akinator, (*curNode(akinator)), *curData(akinator));
                akinatorInsert(akinator, *curNode(akinator), difference);

                free(intended);
                free(difference);
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

curAnchorNode akinatorInsert(akinator_t* akinator, treeNode_t* insertionAddr,  treeVal_t insertVal){
    assert(akinator);
    assert(insertionAddr);

    log(akinator, "before", "insert", insertVal);

    insertionAddr = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    assert(insertionAddr);

    strcpy(insertionAddr->left->data, insertVal);
    insertionAddr->left = NULL;
    insertionAddr->right = NULL;

    LPRINTF("insertionAddr: %p", insertionAddr);

    (akinator->size)++;

    log(akinator, "after", "insert", insertVal);

    return insertionAddr;
}

curAnchorNode akinatorInsertLeft(akinator_t* akinator, treeNode_t* insertionAddr,  treeVal_t insertVal){
    assert(akinator);
    assert(insertionAddr);

    log(akinator, "before", "insert", insertVal);

    insertionAddr->left = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    assert(insertionAddr->left);

    strcpy(insertionAddr->left->data, insertVal);
    insertionAddr->left->left = NULL;
    insertionAddr->left->right = NULL;

    LPRINTF("insertionAddr: %p", insertionAddr->left);

    (akinator->size)++;

    log(akinator, "after", "insert", insertVal);

    return insertionAddr->left;
}

curAnchorNode akinatorInsertRight(akinator_t* akinator, treeNode_t* insertionAddr, treeVal_t insertVal){
    assert(akinator);
    assert(insertionAddr);

    log(akinator, "before", "insert", insertVal);

    insertionAddr->right = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    assert(insertionAddr->right);

    strcpy(insertionAddr->right->data, insertVal);
    insertionAddr->right->left = NULL;
    insertionAddr->right->right = NULL;

    LPRINTF("insertionAddr: %p", insertionAddr->right);

    (akinator->size)++;

    log(akinator, "after", "insert", insertVal);

    return insertionAddr->right;
}

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

