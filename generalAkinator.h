#ifndef GENERAL_AKINATOR_H
#define GENERAL_AKINATOR_H

#include <stddef.h>
#include <limits.h>

#define log(akinator, text, ...) htmlLog(akinator, __FILE__, __FUNCTION__, __LINE__, text, ##__VA_ARGS__)

typedef char* treeVal_t;

// const treeVal_t TREE_POISON = "MEOW";

// enum treeStatus{
//     TREE_PROCESS_OK,
//     TREE_NULL_POINTER,
//     TREE_SIZE_IS_ZERO,
//     TREE_SIZE_EXCEEDS_CAPACITY,
//     TREE_NON_VALID_INDEXES,
//     TREE_LIST_NOT_CONNECTED
// };

// struct treeStatusDescription{
//     treeStatus type;
//     const char* text;
// };

// static struct treeStatusDescription treeStatuses[]{ 
//     {TREE_PROCESS_OK,                    "Все хорошо\n"},
//     {TREE_NULL_POINTER,                  "Указатели не должны быть нулевыми\n"},
//     {TREE_SIZE_IS_ZERO,                  "Capacity равно 0\n"}, 
// };

struct treeNode_t{
    treeVal_t data;
    treeNode_t* right;
    treeNode_t* left;
};

struct akinatorState_t{
    treeNode_t* Node;
};

struct akinator_t{
    treeNode_t*   root;
    size_t        size;
    akinatorState_t curState;
    // treeStatusDescription status;
};

treeVal_t* curData(akinator_t* akinator);
treeNode_t** curNode(akinator_t* akinator);

#endif /* GENERAL_AKINATOR_H */ 