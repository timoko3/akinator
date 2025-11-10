#include "strFunc.h"
#include "hash.h"

#include <assert.h>
#include <stdio.h>

size_t myStrLen(const char* start, char endStr){
    assert(start);

    size_t curSymInd = 0;
    while(start[curSymInd] != endStr) curSymInd++;
    
    return curSymInd;
}

bool isEqualStrings(const char* str1, const char* str2){
    printf("hash answer %s, длина %lu: %ld, hash %s, длина %lu: %ld\n", str1, myStrLen(str1) + 1, hash(str1, myStrLen(str1) + 1), str2, myStrLen(str2) + 1, hash(str2, myStrLen(str2) + 1));
    return hash(str1, myStrLen(str1) + 1) == hash(str2, myStrLen(str2) + 1);
}

size_t countStrings(char* buf, size_t fileSize, char endStr){
    assert(buf);

    size_t nStrings = 1;

    size_t curSym = 0;
    while(curSym < fileSize){
        if(buf[curSym] == endStr){
            nStrings++;
        }
        curSym++;
    }

    return nStrings;
}

void clearBuffer(){
    while(getchar() != '\n'){
        continue;
    }
}

bool isYes(char* answer){
    assert(answer);

    return isEqualStrings(answer, "да");
}

bool isNo(char* answer){
    assert(answer);

    return isEqualStrings(answer, "нет");
}