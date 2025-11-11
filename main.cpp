#include "generalAkinator.h"
#include "protectionAkinator.h"
#include "akinator.h"
#include "akinatorUI.h"
#include "akinatorModes.h"

#include "string.h"
#define DEBUG
#include "general/debug.h"


#include "malloc.h"

int main(void){
    akinator_t akinator;

    akinatorCtor(&akinator);

    runModeMenu(&akinator);

    akinatorDtor(&akinator);
}