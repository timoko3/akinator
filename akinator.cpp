#include "akinator.h"

#define DEBUG
#include "general/debug.h"
#include "general/poison.h"
#include "general/strFunc.h"
#include "general/file.h"

#include "protectionAkinator.h"
#include "akinatorUI.h"

#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

const char* AKINATOR_DATA_BASE_FILE_NAME = "akinatorDataBase.txt";

static void freeNode(treeNode_t* node);

static void akinatorCreateNodeUser(akinator_t* akinator);
static curAnchorNode akinatorCreateNodeFile(akinator_t* akinator, char* buffer, size_t* cuBufferPose);
static curAnchorNode readNode(akinator_t* akinator, char* buffer, size_t* curBufferPos);

static curAnchorNode checkNode(akinator_t* akinator, treeNode_t* curNode, treeVal_t toDefine);

curAnchorNode akinatorCtor(akinator_t* akinator){
    assert(akinator);

    akinator->size = 1;

    akinator->root = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    assert(akinator->root);

    akinator->root->data = (treeVal_t) calloc(MAX_ANSWER_SIZE, sizeof(char));
    assert(akinator->root->data);

    strcpy(akinator->root->data, "someThing");
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

void akinatorReadData(akinator_t* akinator){
    assert(akinator);

    log(akinator, "started reading");

    data_t akinatorData;
    parseStringsFile(&akinatorData, AKINATOR_DATA_BASE_FILE_NAME);

    printf("akinator buffer: %s\n", akinatorData.buffer);

    static size_t curPose = 0;
    readNode(akinator, akinatorData.buffer, &curPose);
    
    free(akinatorData.buffer);
    free(akinatorData.strings);

    log(akinator, "ended reading");
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
                akinatorCreateNodeUser(akinator);
                free(answer);
                break;
            }
            *curNode(akinator) = (*curNode(akinator))->right;
        }

        free(answer);
    }

    *curNode(akinator) = akinator->root;

    log(akinator, "after guess");

    return *curNode(akinator);
}

curAnchorNode akinatorDefine(akinator_t* akinator){
    assert(akinator);

    
    char* toDefine = (char*) calloc(MAX_ANSWER_SIZE, sizeof(char));
    assert(toDefine);

    getWhatDefine(&toDefine);

    checkNode(akinator, akinator->root, toDefine);

    return akinator->root;
}

static curAnchorNode checkNode(akinator_t* akinator, treeNode_t* curNode, treeVal_t toDefine){
    assert(akinator);
    assert(curNode);
    assert(toDefine);

    if(isEqualStrings(curNode->data, toDefine)){
        printf("%s —", toDefine);
        return curNode;
    }

    if(curNode->left){
        checkNode(akinator, curNode->left, toDefine);
    }

    if(curNode->right){
        checkNode(akinator, curNode->right, toDefine);
    }

    return NULL;
}

curAnchorNode akinatorSaveAndExit(akinator_t* akinator){
    assert(akinator);
    
    fileDescription akinatorDataBase{
        AKINATOR_DATA_BASE_FILE_NAME,
        "wb"
    };

    FILE* dataBasePtr = myOpenFile(&akinatorDataBase);
    assert(dataBasePtr);

    printPreOrder(akinator->root, dataBasePtr);

    fclose(dataBasePtr);

    return NULL;
}

curAnchorNode akinatorInsert(akinator_t* akinator, treeNode_t* insertionAddr,  treeVal_t insertVal){
    assert(akinator);
    assert(insertionAddr);
    assert(insertVal);

    log(akinator, "before insert(%s)", insertVal);

    insertionAddr->data = (treeVal_t) calloc(MAX_ANSWER_SIZE, sizeof(char));
    assert(insertionAddr->data);

    strcpy(insertionAddr->data, insertVal);
    insertionAddr->left = NULL;
    insertionAddr->right = NULL;

    LPRINTF("insertionAddr: %p", insertionAddr);

    (akinator->size)++;

    log(akinator, "after insert(%s)", insertVal);

    LPRINTF("INSERT: node=%p data=%p \"%s\"", (void*)insertionAddr, (void*)insertionAddr->data, (char*)insertionAddr->data);

    return insertionAddr;
}

curAnchorNode akinatorInsertLeft(akinator_t* akinator, treeNode_t* insertionAddr,  treeVal_t insertVal){
    assert(akinator);
    assert(insertionAddr);
    assert(insertVal);

    insertionAddr->left = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    assert(insertionAddr->left);

    LPRINTF("NEW NODE: parent=%p -> left=%p (or right) allocated", (void*)insertionAddr, (void*)insertionAddr->left);


    akinatorInsert(akinator, insertionAddr->left, insertVal);

    return insertionAddr->left;
}

curAnchorNode akinatorInsertRight(akinator_t* akinator, treeNode_t* insertionAddr, treeVal_t insertVal){
    assert(akinator);
    assert(insertionAddr);
    assert(insertVal);

    insertionAddr->right = (treeNode_t*) calloc(1, sizeof(treeNode_t));
    assert(insertionAddr->right);

    LPRINTF("NEW NODE: parent=%p -> left=%p (or right) allocated", (void*)insertionAddr, (void*)insertionAddr->left);


    akinatorInsert(akinator, insertionAddr->right, insertVal);

    return insertionAddr->right;
}

void printPreOrder(const treeNode_t* node, FILE* stream){
    assert(node);
    assert(stream);

    fprintf(stream, "(");
    fprintf(stream, "\"%s\" ", node->data);
    
    if(node->left){
        printPreOrder(node->left, stream);
    }
    else{
        fprintf(stream, "nil ");
    }

    if(node->right){
        printPreOrder(node->right, stream);
    }
    else{
        fprintf(stream, "nil ");
    }

    fprintf(stream, ")");
}

void printInOrder(const treeNode_t* node, FILE* stream){
    assert(node);
    assert(stream);

    fprintf(stream, "(");

    if(node->left){
        printInOrder(node->left, stream);
    }
    
    fprintf(stream, "%s", node->data);

    if(node->right){
        printInOrder(node->right, stream);
    }

    fprintf(stream, ")");
}


void printPostOrder(const treeNode_t* node, FILE* stream){
    assert(node);
    assert(stream);
    fprintf(stream, "(");

    if(node->left){
        printPostOrder(node->left, stream);
    }
    if(node->right){
        printPostOrder(node->right, stream);
    }
    fprintf(stream, "%s", node->data);

    fprintf(stream, ")");
}

static void freeNode(treeNode_t* node){
    assert(node);
    
    LPRINTF("FREENODE: node=%p data=%p \"%s\" left=%p right=%p",
        (void*)node, (void*)node->data, node->data ? (char*)node->data : "(null)",
        (void*)node->left, (void*)node->right);

    if(node->left){
        freeNode(node->left);
    }

    if(node->right){
        freeNode(node->right);
    }
    free(node->data);
    poisonMemory(node, sizeof(*node));
    free(node);
    node = NULL;
}

static void akinatorCreateNodeUser(akinator_t* akinator){
    assert(akinator);

    char* intended = (char*) calloc(MAX_ANSWER_SIZE, sizeof(char));
    assert(intended);
    getIntended(akinator, &intended);
    akinatorInsertLeft(akinator, (*curNode(akinator)), intended);

    char* difference = (char*) calloc(MAX_ANSWER_SIZE, sizeof(char));
    assert(difference);
    getDifference(akinator, intended, &difference);
    akinatorInsertRight(akinator, (*curNode(akinator)), *curData(akinator));

    *curData(akinator) = myStrCpy(*curData(akinator), difference);

    
    free(intended);
    free(difference);
}

static curAnchorNode readNode(akinator_t* akinator, char* buffer, size_t* curBufferPos){
    assert(akinator);
    assert(buffer);

    static size_t logNumber = 0;
    log(akinator, "startReadNode %lu", logNumber);
    logNumber++;

    while(true){
        if((buffer[*curBufferPos] == ')') || (buffer[*curBufferPos] == ' ')){
            (*curBufferPos)++;
        }
        else{
            break;
        }
    }

    treeNode_t* createdNode = NULL;
    
    if((buffer[*curBufferPos] == '(') ){
        LPRINTF("скобочка\n");
        createdNode = akinatorCreateNodeFile(akinator, buffer, curBufferPos);
    }
    else{
        treeVal_t curNodeData = (treeVal_t) calloc(MAX_ANSWER_SIZE, sizeof(char));
        assert(curNodeData);

        LPRINTF("буфер перед чтением: %s", &buffer[*curBufferPos]);
        size_t lenName = 0;
        sscanf(&buffer[*curBufferPos], "%s%n", curNodeData, &lenName);
        LPRINTF("Прочиталось внутри случая nil: %s", curNodeData);
        if(isEqualStrings(curNodeData, "nil")){
            LPRINTF("Зашел в nil");
            *curBufferPos += lenName;
            LPRINTF("буфер после чтения: %s\n", &buffer[*curBufferPos]);
            free(curNodeData);
            return NULL;
        }

        free(curNodeData);
    }

    LPRINTF("адрес текущей созданной ноды: %p", createdNode);
    (*curBufferPos)++;
    LPRINTF("\n\nрекурсивный запуск");
    createdNode->left  = readNode(akinator, buffer, curBufferPos);
    createdNode->right = readNode(akinator, buffer, curBufferPos);

    
    (akinator->size)++;

    log(akinator, "endReadNode %lu", logNumber);

    return createdNode;
}


static curAnchorNode akinatorCreateNodeFile(akinator_t* akinator, char* buffer, size_t* curBufferPose){
    assert(akinator);
    assert(buffer);
    
    treeNode_t* curNode;

    static size_t countNodes = 1;
    if(countNodes == 1){
        curNode = akinator->root;
        (akinator->size)--;
    }
    else{
        curNode = (treeNode_t*) calloc(1, sizeof(treeNode_t));
        assert(curNode);
        LPRINTF("Выделил память");
        curNode->data = (treeVal_t) calloc(MAX_ANSWER_SIZE, sizeof(char));
        assert(curNode->data);
    }
    countNodes++;
    


    (*curBufferPose)++;
    
    LPRINTF("записал указатель в data нового node");
    size_t lenName = 0;

    treeVal_t curNodeData = (treeVal_t) calloc(MAX_ANSWER_SIZE, sizeof(char));
    assert(curNodeData);

    LPRINTF("буфер перед чтением: %s", &buffer[*curBufferPose]);

    sscanf(&buffer[*curBufferPose], "\"%[^\"]\"%n", curNodeData, &lenName);
    LPRINTF("Получил размер строки %lu и саму строку %s", lenName, curNodeData);
    strcpy(curNode->data, curNodeData);
    *curBufferPose += lenName;
    LPRINTF("\nбуфер после чтением: %s", &buffer[*curBufferPose]);

    free(curNodeData);
    return curNode;
}