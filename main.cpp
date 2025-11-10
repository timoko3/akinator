#include "generalAkinator.h"
#include "protectionAkinator.h"
#include "akinator.h"
#include "akinatorUI.h"
#include "akinatorModes.h"

#include "string.h"

#include "malloc.h"

int main(void){
    akinator_t akinator;

    akinatorCtor(&akinator);

    log(&akinator, "test");
        
    showMenu();
    menuModeVal_t modeNum = getMode();
    runMode(modeNum, &akinator);

    akinatorDtor(&akinator);
}