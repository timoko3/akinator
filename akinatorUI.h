#include "generalAkinator.h"

typedef int menuModeVal_t;  

void showMenu();
menuModeVal_t getMode();

void askQuestionUser(akinator_t* akinator);
char* getAnswerUser(akinator_t* akinator);