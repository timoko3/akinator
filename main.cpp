#define TX_USE_SPEAK
#include "TXLib.h" 

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

    animation();

    akinatorCtor(&akinator);

    akinatorReadData(&akinator);

    runModeMenu(&akinator);

    akinatorDtor(&akinator);
}