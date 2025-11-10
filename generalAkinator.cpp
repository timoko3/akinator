#include "generalAkinator.h"

#include <assert.h>


treeVal_t* curData(akinator_t* akinator){
    assert(akinator);

    return &akinator->curState.Node->data;
}

treeNode_t* curNode(akinator_t* akinator){
    assert(akinator);

    return akinator->curState.Node;
}