#include "akinatorModes.h"
#include "akinatorUI.h"

#include <assert.h>
#include <stdio.h>

static handler_t findHandler(modeNum num);

void runModeMenu(akinator_t* akinator){
    assert(akinator);

    while(true){
        showMenu();
        menuModeVal_t userModeNum = getMode();
        if(!runMode(userModeNum, akinator)) return;
    }
}

bool runMode(modeNum num, akinator_t* akinator){
    assert(akinator);

    handler_t handler = findHandler(num);
    assert(handler);


    if(!handler(akinator))return false;
    return true;
}

static handler_t findHandler(modeNum num){
    printf("num = %d\n", num);
    printf("size: %lu\n", sizeof(modes) / sizeof(mode_t));
    for(size_t curMode = 0; curMode < sizeof(modes) / sizeof(mode_t); curMode++){
        if((modeNum) curMode == num){
            return modes[curMode].modeFunc;
        }
    }

    return NULL;
}