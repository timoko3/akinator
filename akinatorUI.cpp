#define TX_USE_SPEAK
#include "TXLib.h"

#include "akinatorUI.h"
#include "generalAkinator.h"
#include "general/strFunc.h"
#include "general/hash.h"
#include "akinatorModes.h"
#define DEBUG
#include "general/debug.h"
#include "genConsoleColors/consoleColors.h"

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdarg.h>

const char* const ALERT_MENU_INCORRECT = "Выбирайте из предложенных вариантов\n";
const char* const CHOOSE_YES_OR_NO     = "Выбирайте да или нет\n";
const menuModeVal_t  MENU_FIRST_ITEM = 1; 
const menuModeVal_t  EXIT            = 4;


void showMenu(){
    static size_t countShowMenu = 0;

    printf("Выберите одну из доступных опций: " SET_STYLE_BOLD_FONT_PURPLE "1)" RESET "Отгадывать " SET_STYLE_BOLD_FONT_PURPLE "2)" RESET "Определение " SET_STYLE_BOLD_FONT_PURPLE "3)" RESET "Сравнение " SET_STYLE_BOLD_FONT_PURPLE "4)" RESET "Выйти\n");
    tellWithAnimation("\aВыберите одну из доступных опций:");
    
    if(countShowMenu == 0){
        tellWithAnimation("\aМогу отгадать, что ты загадал");
        tellWithAnimation("\aМогу дать определение");
        tellWithAnimation("\aМогу сравнить два объекта");
        tellWithAnimation("\aНу а если не устраивают иди нафиг и уходи");
    }

    countShowMenu++;
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
    tellWithAnimation("\aЭто %s?", *curData(akinator));

    printf("%s?\n", *curData(akinator));
}

char* getAnswerUser(akinator_t* akinator){
    assert(akinator);

    char* answer = (char*) calloc(MAX_ANSWER_SIZE, sizeof(char));
    assert(answer);

    while((!scanf("%s", answer)) || (!isYes(answer) && !isNo(answer))){
        LPRINTF("answer: %s\n", answer);
        LPRINTF("isYes: %d", isYes(answer));
        printf("%s", CHOOSE_YES_OR_NO);
        clearBuffer();
    }

    clearBuffer();

    return answer;
}

void printResult(akinator_t* akinator){
    assert(akinator);

    tellWithAnimation("\aТебе не провести меня кожаный мешок!");

    tellWithAnimation("\aЭто %s", *curData(akinator));
    printf("Опять Я угадал! Это %s\n", *curData(akinator));
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

    tellWithAnimation("\aговори уже кто был загадан");

    printf("Кто был загадан?\n");

    return getString(answer);
}

char* getDifference(akinator_t* akinator, char* intended, char** difference){
    assert(akinator);
    assert(intended);
    assert(difference);

    tellWithAnimation("\aКакие отличия у %s и %s", intended, (*curNode(akinator))->data);

    printf("Чем %s отличается от %s?\n", intended, (*curNode(akinator))->data);

    return getString(difference);
}


char* getWhatDefine(char** toDefine){
    assert(toDefine);

    tellWithAnimation("\aОпять мне надо все объяснять резервуарам с биологическими жидкостями");
    tellWithAnimation("\aКому ты хочешь чтобы я дал определение?");

    printf("Кому вы хотите, чтобы я дал определение?\n");

    return getString(toDefine);
}

char* getWhatCompare(char** toCompare){
    assert(toCompare);

    printf("Введите кого вы хотите сравнить\n");

    return getString(toCompare);
}

void printComparisonResults(akinator_t* akinator, size_t depth1, size_t depth2, 
        treeNode_t* compareNode1, treeNode_t* compareNode2){
    assert(akinator);
    assert(compareNode1);
    assert(compareNode2);

    treeVal_t firstCompNodeName  = compareNode1->data;
    treeVal_t secondCompNodeName = compareNode2->data;

    while (depth1 > depth2) { 
        compareNode1 = compareNode1->parent;
        depth1--;
    }

    while (depth2 > depth1) {
        compareNode2 = compareNode2->parent;
        depth2--;
    }

    treeNode_t* firstBeforeEqualNode1 = NULL;
    while (compareNode1 && compareNode2 && (compareNode1 != compareNode2)) {
        firstBeforeEqualNode1 = compareNode1;
        compareNode1 = compareNode1->parent;

        compareNode2 = compareNode2->parent;
    }

    printf("\n");

    if(compareNode1->left == firstBeforeEqualNode1){
        tellWithAnimation("\a%s отличатеся от %s тем, что %s %s, a %s не %s", firstCompNodeName, secondCompNodeName, firstCompNodeName, compareNode1->data, secondCompNodeName, compareNode1->data);
        printf(SET_STYLE_ITALICS_FONT_YELLOW "%s" RESET " отличатеся от " SET_STYLE_ITALICS_FONT_TURQUOISE "%s" RESET " тем, что " SET_STYLE_ITALICS_FONT_YELLOW "%s" RESET " %s, a " SET_STYLE_ITALICS_FONT_TURQUOISE "%s" RESET " не %s. ", firstCompNodeName, secondCompNodeName,
            firstCompNodeName, compareNode1->data, secondCompNodeName, compareNode1->data);
    }
    else{
        tellWithAnimation("\a%s отличатеся от %s тем, что %s %s, a %s не %s", secondCompNodeName, firstCompNodeName, secondCompNodeName, compareNode1->data, firstCompNodeName, compareNode1->data);
        printf(SET_STYLE_ITALICS_FONT_TURQUOISE "%s" RESET " отличатеся от " SET_STYLE_ITALICS_FONT_YELLOW "%s" RESET " тем, что " SET_STYLE_ITALICS_FONT_TURQUOISE "%s" RESET " %s, a " SET_STYLE_ITALICS_FONT_YELLOW "%s" RESET " не %s. ", secondCompNodeName, firstCompNodeName,
            secondCompNodeName, compareNode1->data, firstCompNodeName, compareNode1->data);
    }

    tellWithAnimation("\aИ %s и %s оба", firstCompNodeName, secondCompNodeName);
    if(compareNode1->parent){
        printf("И " SET_STYLE_ITALICS_FONT_YELLOW "%s" RESET ", и " SET_STYLE_ITALICS_FONT_TURQUOISE "%s" RESET " оба ", firstCompNodeName, secondCompNodeName);
    }
    while(compareNode1->parent){
        if(compareNode1->parent->left == compareNode1){
            tellWithAnimation("\a%s", compareNode1->parent->data);
            if(compareNode1->parent->parent){
                printf("%s, ", compareNode1->parent->data);
            }
            else{
                printf("%s.", compareNode1->parent->data);
            }
        }
        else{
            tellWithAnimation("\aне %s", compareNode1->parent->data);
            if(compareNode1->parent->parent){
                printf("не %s, ", compareNode1->parent->data);
            }
            else{
                printf("не %s.", compareNode1->parent->data);
            }
        }
        compareNode1 = compareNode1->parent;
    }

    printf("\n\n");
}

void printDefinition(treeNode_t* curNode, treeVal_t toDefine){
    assert(curNode);
    assert(toDefine);

    tellWithAnimation("\a%s", toDefine);
    printf(SET_STYLE_BOLD_FONT_BLUE "%s" RESET " — ", toDefine);
    printParent(curNode);
}

void printParent(treeNode_t* curNode){
    assert(curNode);
    
    static treeNode_t* defineNodeAddr = curNode;

    if(curNode->parent){
        printParent(curNode->parent);
    }
    else{
        return;
    }

    if(curNode->parent->left == curNode){
        tellWithAnimation("\a%s", curNode->parent->data);
        printf("%s", curNode->parent->data);

        if(curNode != defineNodeAddr){
            printf(", ");
        }
        else{
            printf(".");
        }
    }
    else{
        tellWithAnimation("\aне %s", curNode->parent->data);
        printf("не %s", curNode->parent->data);

        if(curNode != defineNodeAddr){
            printf(", ");
        }
        else{
            printf(".");
        }
        
    }    
}

void animation(size_t delay){
    static size_t countAnimationCalls = 0;
    if(countAnimationCalls == 0){
        txCreateWindow (750, 750);
    }
    countAnimationCalls++;

    for(size_t curFrame = 0; curFrame < 31; curFrame++){
        
        char frameName[50] = "";

        sprintf(frameName, "animation/OmnX-%llu.bmp", curFrame);

        HDC frame = txLoadImage (frameName, 750, 750);

        if (!frame)
            txMessageBox ("Не могу загрузить");

        txBitBlt (txDC(), 0, 0, 1200, 900, frame, 0, 0);

        txDeleteDC (frame);
        txSleep((double) delay);
    }

}

void tellWithAnimation(const char* text, ...){
    assert(text);

    char phrase[MAX_ANSWER_SIZE];

    va_list args;
    va_start(args, text);
    vsprintf(phrase, text, args);
    va_end(args);

    size_t delay = myStrLen(phrase) * 73 / 30;

    txSpeak(phrase);
    animation(delay);
}
