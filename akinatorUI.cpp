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
const size_t         MAX_ANSWER_SIZE = 256;

void showMenu(){
    printf("Выберите одну из доступных опций: 1)Отгадывать 2) Выйти\n");
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

    return answer;
}



void printResult(akinator_t* akinator){
    assert(akinator);

    printf("Опять Я угадал! Это %s", *curData(akinator));
}

char* getIntended(akinator_t* akinator){
    assert(akinator);

    printf("Кого вы загадали?\n");

    char* answer = (char*) calloc(MAX_ANSWER_SIZE, sizeof(char));
    assert(answer);

    while(!scanf("%s", answer)){
        printf("answer: %s\n", answer);
        printf("isYes: %d", isYes(answer));
        printf("%s", "Некорректный ввод");
        clearBuffer();
    }

    return answer;
}

char* getDifference(akinator_t* akinator, char* intended){
    assert(akinator);
    assert(intended);

    printf("Чем %s отличается от %s?", intended, (*curNode(akinator))->data);

    char* difference = (char*) calloc(MAX_ANSWER_SIZE, sizeof(char));
    assert(difference);

    while(!scanf("%s", difference)){
        printf("difference: %s\n", difference);
        printf("%s", "Некорректный ввод");
        clearBuffer();
    }

    return difference;
}

