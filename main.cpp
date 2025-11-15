

#include "generalAkinator.h"
#include "protectionAkinator.h"
#include "akinator.h"
#include "akinatorUI.h"
#include "akinatorModes.h"

#define DEBUG
#include "general/debug.h"


#include "malloc.h"

int main(void){
    akinator_t akinator;

    tellWithAnimation("\aПривет всем кожаным мешкам!");

    akinatorCtor(&akinator);

    akinatorReadData(&akinator);

    runModeMenu(&akinator);

    akinatorDtor(&akinator);

    return 0;
}