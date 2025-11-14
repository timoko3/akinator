#include "akinatorUI.h"
#include "generalAkinator.h"
#include "general/strFunc.h"
#include "general/hash.h"
#include "akinatorModes.h"

#include <stdio.h>
#include <assert.h>
#include <malloc.h>


const char* const ALERT_MENU_INCORRECT = "Выбирайте из предложенных вариантов\n";
const char* const CHOOSE_YES_OR_NO     = "Выбирайте да или нет\n";
const menuModeVal_t  MENU_FIRST_ITEM = 1; 
const menuModeVal_t  EXIT            = 4;


void showMenu(){
    printf("Выберите одну из доступных опций: 1)Отгадывать 2)Определение 3)Сравнение 4)Выйти\n");
}

menuModeVal_t getMode(){
    menuModeVal_t mode = 0;

    while(!(scanf("%d", &mode)) || mode < MENU_FIRST_ITEM || mode > EXIT){
        printf("%s", ALERT_MENU_INCORRECT);
        clearBuffer();
    }
    assert(!(mode < MENU_FIRST_ITEM || mode > EXIT));

    clearBuffer();
    return mode - MENU_FIRST_ITEM;
}

void askQuestionUser(akinator_t* akinator){
    assert(akinator);

    printf("%s?\n", *curData(akinator));
}

char* getAnswerUser(akinator_t* akinator){
    assert(akinator);

    char* answer = (char*) calloc(MAX_ANSWER_SIZE, sizeof(char));
    assert(answer);
    printf("%lu\n", malloc_usable_size(answer));


    while((!scanf("%s", answer)) || (!isYes(answer) && !isNo(answer))){
        printf("answer: %s\n", answer);
        printf("isYes: %d", isYes(answer));
        printf("%s", CHOOSE_YES_OR_NO);
        clearBuffer();
    }

    clearBuffer();

    return answer;
}

void printResult(akinator_t* akinator){
    assert(akinator);

    printf("Опять Я угадал! Это %s", *curData(akinator));
}

char* getString(char** buffer){
    assert(buffer);

    while(!myFGets(*buffer, MAX_ANSWER_SIZE, stdin)){
        printf("%s", "Некорректный ввод\n");
        clearBuffer();
    }

    return *buffer;
}

char* getIntended(akinator_t* akinator, char** answer){
    assert(akinator);

    printf("Кто был загадан?\n");

    return getString(answer);
}

char* getDifference(akinator_t* akinator, char* intended, char** difference){
    assert(akinator);
    assert(intended);
    assert(difference);

    printf("Чем %s отличается от %s?\n", intended, (*curNode(akinator))->data);

    return getString(difference);
}


char* getWhatDefine(char** toDefine){
    assert(toDefine);

    printf("Чему вы хотите, чтобы я дал определение?\n");

    return getString(toDefine);
}

char* getWhatCompare(char** toCompare){
    assert(toCompare);

    printf("Введите кого вы хотите сравнить\n");

    return getString(toCompare);
}

void printComparisonResults(size_t depth1, size_t depth2, 
        treeNode_t* compareNode1, treeNode_t* compareNode2){
    assert(compareNode1);
    assert(compareNode2);

    treeVal_t firstCompNodeName  = compareNode1->data;
    treeVal_t secondCompNodeName = compareNode2->data;

    while (depth1 > depth2) { 
        if(compareNode1->parent->left == compareNode1){
            printf("%s: %s\n", firstCompNodeName, compareNode1->parent->data);
        }
        else{
            printf("%s: не %s\n", firstCompNodeName, compareNode1->parent->data);
        }
        compareNode1 = compareNode1->parent;
        depth1--;
    }

    while (depth2 > depth1) {
        if(compareNode2->parent->left == compareNode2){
            printf("%s: %s\n", secondCompNodeName, compareNode2->parent->data);
        }
        else{
            printf("%s: не %s\n", secondCompNodeName, compareNode2->parent->data);
        }
        compareNode2 = compareNode2->parent;
        depth2--;
    }
    printf("\n");
    
    while (compareNode1 && compareNode2 && (compareNode1 != compareNode2)) {
        if(compareNode1->parent->left == compareNode1){
            printf("%s: %s\n", firstCompNodeName, compareNode1->parent->data);
        }
        else{
            printf("%s: не %s\n", firstCompNodeName, compareNode1->parent->data);
        }
        
        if(compareNode2->parent->left == compareNode2){
            printf("%s: %s\n", secondCompNodeName, compareNode2->parent->data);
        }
        else{
            printf("%s: не %s\n", secondCompNodeName, compareNode2->parent->data);
        }
        compareNode1 = compareNode1->parent;
        compareNode2 = compareNode2->parent;
    }
    
    
    printf("%s и %s — ", firstCompNodeName, secondCompNodeName);
    while(compareNode1->parent){
        if(compareNode1->parent->left == compareNode1){
            printf("%s, ", compareNode1->parent->data);
        }
        else{
            printf("не %s,", compareNode1->parent->data);
        }
        compareNode1 = compareNode1->parent;
    }

    printf("\n");
}