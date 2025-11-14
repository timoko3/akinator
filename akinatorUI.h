#include "generalAkinator.h"

typedef int menuModeVal_t;  

void showMenu();
menuModeVal_t getMode();

void askQuestionUser(akinator_t* akinator);
char* getAnswerUser(akinator_t* akinator);
void printResult(akinator_t* akinator);


char* getString(char** buffer);
char* getIntended(akinator_t* akinator, char** intended);
char* getDifference(akinator_t* akinator, char* intended, char** difference);
char* getWhatDefine(char** toDefine);
char* getWhatCompare(char** toCompare);