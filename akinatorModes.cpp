#include "akinatorModes.h"

#include <assert.h>
#include <stdio.h>

static handler_t findHandler(modeNum num);

void runMode(modeNum num, akinator_t* akinator){
    assert(akinator);

    handler_t handler = findHandler(num);

    handler(akinator);
}

static handler_t findHandler(modeNum num){
    printf("num = %d\n", num);
    printf("size: %lu\n", sizeof(modes) / sizeof(mode_t));
    for(size_t curMode = 0; curMode < sizeof(modes) / sizeof(mode_t); curMode++){
        if(curMode == num){
            return modes[curMode].modeFunc;
        }
    }

    return NULL;
}