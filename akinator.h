#ifndef AKINATOR_H
#define AKINATOR_H

#include "generalAkinator.h"

typedef treeNode_t* curAnchorNode;

curAnchorNode akinatorCtor(akinator_t* tree);
curAnchorNode treeDtor(akinator_t* tree);

// curAnchorNode treeSortInsert(akinator_t* tree, treeVal_t insertVal);

void printPreOrder(const treeNode_t* node);
void printInOrder(const treeNode_t* node);
void printPostOrder(const treeNode_t* node);

#endif /* AKINATOR_H */