#ifndef AKINATOR_H
#define AKINATOR_H

#include "generalAkinator.h"

#include "stdio.h"

typedef treeNode_t* curAnchorNode;

curAnchorNode akinatorCtor(akinator_t* akinator);
curAnchorNode akinatorDtor(akinator_t* akinator);
void akinatorReadData(akinator_t* akinator);

curAnchorNode akinatorInsertLeft(akinator_t* akinator, treeNode_t* insertionAddr,  treeVal_t insertVal);
curAnchorNode akinatorInsertRight(akinator_t* akinator, treeNode_t* insertionAddr,  treeVal_t insertVal);
curAnchorNode akinatorInsert(akinator_t* akinator, treeNode_t* insertionAddr,  treeVal_t insertVal);
curAnchorNode akinatorGuess(akinator_t* akinator);
curAnchorNode akinatorDefine(akinator_t* akinator);
curAnchorNode akinatorSaveAndExit(akinator_t* akinator);

void printPreOrder (const treeNode_t* node, FILE* stream);
void printInOrder  (const treeNode_t* node, FILE* stream);
void printPostOrder(const treeNode_t* node, FILE* stream);

#endif /* AKINATOR_H */