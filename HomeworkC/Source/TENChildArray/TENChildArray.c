//
//  TENChildArray.c
//  HomeworkC
//
//  Created by 444ten on 3/2/15.
//  Copyright (c) 2015 444ten. All rights reserved.
//

#include "TENChildArray.h"
#include "TENHuman.h"

static const uint8_t TENIndexNotFound = -1;
static const uint8_t TENDefaultSize = 5;

#pragma mark -
#pragma mark Private Declarations

static
TENHuman **TENChildArrayGetArray(TENChildArray *childArray);

#pragma mark -
#pragma mark Public Implementations

void __TENChildArrayDeallocate(TENChildArray *childArray) {
    for (int i = 0; i < childArray->_childrenCount; i++) {
        free(childArray->_array[i]);
        childArray->_array[i] = NULL;
    }
    
    __TENObjectDeallocate(childArray);
}

void TENChildArrayAlloc(TENChildArray *childArray) {
    if (TENDefaultSize != childArray->_size) {
        childArray->_size = TENDefaultSize;
        childArray->_array = calloc(childArray->_size, sizeof(*childArray->_array));        
    }
}

uint8_t TENChildArrayGetChildrenCount(TENChildArray *childArray) {
    return (NULL != childArray) ? childArray->_childrenCount : 0;
}

void TENChildArrayAddObject(TENChildArray *childArray, TENHuman *object) {
    TENChildArrayAlloc(childArray);
    childArray->_array[childArray->_childrenCount] = object;
    childArray->_childrenCount += 1;
    TENRetain(object);
}

uint8_t TENChildArrayIndexOfObject(TENChildArray *childArray, TENHuman *object) {
    uint8_t indexObject = 0;
    
    for (; childArray->_array[indexObject] != object; indexObject++) {
        if (indexObject >= childArray->_childrenCount) {
            return TENIndexNotFound;
        }
    }
    
    return indexObject;
}

void TENChildArrayRemoveObjectAtIndex(TENChildArray *childArray, uint8_t index) {
    if (TENIndexNotFound != index) {
        childArray->_childrenCount -= 1;
        TENRelease(childArray->_array[index]);
        
        for (; index < childArray->_childrenCount; index++) {
            childArray->_array[index] = childArray->_array[index + 1];
        }
        
        childArray->_array[childArray->_childrenCount] = NULL;
        TENChildArrayAlloc(childArray);
    }
}

void TENChildArrayPrint(TENChildArray *childArray) {
    uint8_t childrenCount = TENChildArrayGetChildrenCount(childArray);
    
    if (NULL != childArray && childrenCount > 0) {
        printf(" total %d: ", childrenCount);
        for (int i = 0; i < childrenCount; i++) {
            printf("%s ", TENStringGetData(TENHumanGetName(TENChildArrayGetArray(childArray)[i])));
        }
        
        printf("\n");
    }
}

#pragma mark -
#pragma mark Private Implementations

TENHuman **TENChildArrayGetArray(TENChildArray *childArray) {
    return (NULL != childArray) ? childArray->_array : NULL;
}
