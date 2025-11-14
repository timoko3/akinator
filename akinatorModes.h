#include "generalAkinator.h"
#include "akinator.h"

typedef int modeNum;
typedef curAnchorNode (*handler_t)(akinator_t* akinator);

struct akinator_mode_t{
    modeNum num;
    handler_t modeFunc;
};

static akinator_mode_t modes[] = {
    {0, akinatorGuess},
    {1, akinatorDefine},
    {2, akinatorCompare},
    {3, akinatorSaveAndExit}
};


void runModeMenu(akinator_t* akinator);
bool runMode(modeNum num, akinator_t* akinator);