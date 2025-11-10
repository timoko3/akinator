#ifndef TREE_PROTECTION_H
#define TREE_PROTECTION_H

#include "generalAkinator.h"

#include <stdio.h>

void htmlLog(akinator_t* akinator, const char* callFileName, const char* callFuncName, int callLine,
                           const char* dumpDescription, ...);
void treeGraphDump(akinator_t* akinator);
// treeStatus verifyTree(akinator_t* tree, const char* function, const char* file, const int line);

#endif /* TREE_PROTECTION_H */