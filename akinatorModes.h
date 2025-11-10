#include "generalAkinator.h"
#include "akinator.h"

typedef int modeNum;
typedef curAnchorNode (*handler_t)(akinator_t* akinator);

struct mode_t{
    modeNum num;
    handler_t modeFunc;
};

static mode_t modes[] = {
    {0, akinatorGuess},
    {1, akinatorSaveAndExit}
};


void runMode(modeNum num, akinator_t* akinator);