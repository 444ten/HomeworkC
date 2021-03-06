//
//  TENLinkedListTests.c
//  HomeworkC
//
//  Created by 444ten on 3/26/15.
//  Copyright (c) 2015 444ten. All rights reserved.
//

#include <assert.h>

#include "TENLinkedList.h"
#include "TENLinkedListPrivate.h"
#include "TENLinkedListEnumerator.h"
#include "TENLinkedListTests.h"
#include "TENNode.h"
#include "TENObject.h"

#pragma mark -
#pragma mark Private Declarations

static
void TENLinkedListAddNodeTest();

static
void TENLinkedListRemoveNodeTest();

static
void TENLinkedListEmtyEnumeratorTest();

static
void TENLinkedListEnumeratorTest();

static
void TENLinkedListRemoveObjectTest();

static
void TENLinkedListInsertObjectBeforeObjectTest();

static
void TENLinkedListInsertObjectAfterObjectTest();

#pragma mark -
#pragma mark Public Implementations

extern
void TENLinkedListPerformTests() {
    TENLinkedListAddNodeTest();
    TENLinkedListRemoveNodeTest();
    TENLinkedListEmtyEnumeratorTest();
    TENLinkedListEnumeratorTest();
    TENLinkedListRemoveObjectTest();
    TENLinkedListInsertObjectBeforeObjectTest();
    TENLinkedListInsertObjectAfterObjectTest();

}

#pragma mark -
#pragma mark Private Implementations

static
void TENLinkedListAddNodeTest() {
    // TENLinkedList
    //  after being created
    TENLinkedList *list = TENObjectCreate(TENLinkedList);

    //      after add (TENObject *)stack1
    TENObject *stack1 = TENObjectCreate(TENObject);
    TENLinkedListAddObject(list, stack1);
    
    //          it count should equal 1
    assert(1 == TENLinkedListGetCount(list));
    
    //          it mutationCount should equal 1
    assert(1 == TENLinkedListGetMutationCount(list));
    
    //          it rootNode->stack should equal stack1
    assert(stack1 == TENNodeGetStack(TENLinkedListGetRootNode(list)));
    
    //              after add (TENObject *)stack2
    TENObject *stack2 = TENObjectCreate(TENObject);
    TENLinkedListAddObject(list, stack2);

    //                  it count should equal 2
    assert(2 == TENLinkedListGetCount(list));
    
    //                  it mutationCount should equal 2
    assert(2 == TENLinkedListGetMutationCount(list));
    
    //                  it rootNode->stack should equal stack2
    assert(stack2 == TENNodeGetStack(TENLinkedListGetRootNode(list)));
    
    //                  it nextNode->stack should equal stack1
    TENNode *nextNode = TENNodeGetNextNode(TENLinkedListGetRootNode(list));
    assert(stack1 == TENNodeGetStack(nextNode));

    TENRelease(stack1);
    TENRelease(stack2);
    TENRelease(list);
}

void TENLinkedListRemoveNodeTest() {
    // TENLinkedList
    //  after being created and added five unique stacks
    //      after removeFirstNode
    //          it count should equal 2
    //          it mutationCount should equal 4
    //          it rootNode->stack should equal stack2
    //          it nextNode->stack should equal stack1
    //              after remove all stacks
    //                  it count should equal 0
    //                  it rootNode should equal NULL
    
    TENLinkedList *list = TENObjectCreate(TENLinkedList);
    
    const uint8_t count = 5;
    TENObject *stackArray[count];
    
    for (int i = 0; i < count; i++) {
        stackArray[i] = TENObjectCreate(TENObject);
        TENLinkedListAddObject(list, stackArray[i]);
    }
    
    TENLinkedListRemoveFirstObject(list);

    assert((count - 1) == TENLinkedListGetCount(list));
    
    assert((count + 1) == TENLinkedListGetMutationCount(list));
    
    assert(stackArray[3] == TENNodeGetStack(TENLinkedListGetRootNode(list)));
    
    TENNode *nextNode = TENNodeGetNextNode(TENLinkedListGetRootNode(list));
    assert(stackArray[2] == TENNodeGetStack(nextNode));
    
    TENLinkedListRemoveAllObjects(list);

    assert(0 == TENLinkedListGetCount(list));
    
    assert(NULL == TENLinkedListGetRootNode(list));
    
    for (int i = 0; i < count; i++) {
        TENRelease(stackArray[i]);
    }

    TENRelease(list);
}

void TENLinkedListRemoveObjectTest() {
    //TENLinkedList
    //after being created and added five unique stacks
    TENLinkedList *list = TENObjectCreate(TENLinkedList);
    
    const uint8_t count = 5;
    uint8_t currentCount = count;
    TENObject *stackArray[count];
    
    for (int i = 0; i < count; i++) {
        stackArray[i] = TENObjectCreate(TENObject);
        TENLinkedListAddObject(list, stackArray[i]);
    }

    //after remove stackArray[4] (first object)
    TENLinkedListRemoveObject(list, stackArray[4]);

    //it count should decrease by 1
    currentCount -= 1;
    assert(currentCount == TENLinkedListGetCount(list));
    
    //it rootNode->stack should equal stackArray[3]
    assert(stackArray[3] == TENNodeGetStack(TENLinkedListGetRootNode(list)));
    
    //it should contain stackArray[2]
    assert(TENLinkedListContainsObject(list, stackArray[2]));
    
    //it should not contain stackArray[4]
    assert(!TENLinkedListContainsObject(list, stackArray[4]));
    
    //after remove stackArray[0] (last object)
    TENLinkedListRemoveObject(list, stackArray[0]);

    //it count should decrease by 1
    currentCount -= 1;
    assert(currentCount == TENLinkedListGetCount(list));
    
    //after remove stackArray[2] (middle object)
    TENLinkedListRemoveObject(list, stackArray[2]);
 
    //it count should decrease by 1
    currentCount -= 1;
    assert(currentCount == TENLinkedListGetCount(list));

    //after remove non-included object (stackArray[4])
    TENLinkedListRemoveObject(list, stackArray[4]);
    
    //it count should not change
    assert(currentCount == TENLinkedListGetCount(list));

    //after remove NULL object
    TENLinkedListRemoveObject(list, NULL);

    //it count should not change
    assert(currentCount == TENLinkedListGetCount(list));
    
    //after remove all objects
    TENLinkedListRemoveAllObjects(list);

    //it count should equal 0
    assert(0 == TENLinkedListGetCount(list));

    //after remove object
    TENLinkedListRemoveObject(list, stackArray[4]);

    for (int i = 0; i < count; i++) {
        TENRelease(stackArray[i]);
    }
    
    TENRelease(list);
}

void TENLinkedListInsertObjectBeforeObjectTest() {
    //TENLinkedList
    //after being created and added three unique stacks
    TENLinkedList *list = TENObjectCreate(TENLinkedList);
    
    const uint8_t count = 3;
    uint8_t currentCount = count;

    TENObject *stackArray[count];
    
    for (int i = 0; i < count; i++) {
        stackArray[i] = TENObjectCreate(TENObject);
        TENLinkedListAddObject(list, stackArray[i]);
    }

    //after inserted object1 before stackArray[2] (first object)
    TENObject *object1 = TENObjectCreate(TENObject);
    TENLinkedListInsertObjectBeforeObject(list, object1, stackArray[2]);
    
    //it rootNode->stack should equal object1
    assert(object1 == TENNodeGetStack(TENLinkedListGetRootNode(list)));

    //it count should increase by 1
    currentCount += 1;
    assert(currentCount == TENLinkedListGetCount(list));
    
    //after inserted object2 before stackArray[0] (last object)
    TENObject *object2 = TENObjectCreate(TENObject);
    TENLinkedListInsertObjectBeforeObject(list, object2, stackArray[0]);
    
    //it count should increase by 1
    currentCount += 1;
    assert(currentCount == TENLinkedListGetCount(list));
    
    //after remove first object three times
    for (int i = 0; i < 3; i++) {
        TENLinkedListRemoveFirstObject(list);
        currentCount -= 1;
    }
    
    //it count should decrease by 3
    assert(currentCount == TENLinkedListGetCount(list));

    //it rootNode->stack should equal object2
    assert(object2 == TENNodeGetStack(TENLinkedListGetRootNode(list)));
    
    //after inserted object1 before stackArray[1] (not-included object)
    TENLinkedListInsertObjectBeforeObject(list, object1, stackArray[1]);
    
    //it count should not change
    assert(currentCount == TENLinkedListGetCount(list));
    
    //after inserted NULL before NULL
    TENLinkedListInsertObjectBeforeObject(list, NULL, NULL);
    
    //it count should not change
    assert(currentCount == TENLinkedListGetCount(list));
    
    for (int i = 0; i < count; i++) {
        TENRelease(stackArray[i]);
    }
    
    TENRelease(object1);
    TENRelease(object2);
    TENRelease(list);
}


void TENLinkedListInsertObjectAfterObjectTest() {
    //TENLinkedList
    //after being created and added two unique stacks
    TENLinkedList *list = TENObjectCreate(TENLinkedList);
    
    const uint8_t count = 2;
    uint8_t currentCount = count;
    
    TENObject *stackArray[count];
    
    for (int i = 0; i < count; i++) {
        stackArray[i] = TENObjectCreate(TENObject);
        TENLinkedListAddObject(list, stackArray[i]);
    }
    
    //after inserted object1 after stackArray[1] (first object)
    TENObject *object1 = TENObjectCreate(TENObject);
    TENLinkedListInsertObjectAfterObject(list, object1, stackArray[1]);
    
    //it count should increase by 1
    currentCount += 1;
    assert(currentCount == TENLinkedListGetCount(list));
    
    //after inserted object2 after stackArray[0] (last object)
    TENObject *object2 = TENObjectCreate(TENObject);
    TENLinkedListInsertObjectAfterObject(list, object2, stackArray[0]);
    
    //it count should increase by 1
    currentCount += 1;
    assert(currentCount == TENLinkedListGetCount(list));

    //after remove first object
    TENLinkedListRemoveFirstObject(list);
    currentCount -= 1;

    //it rootNode->stack should equal object1
    assert(object1 == TENNodeGetStack(TENLinkedListGetRootNode(list)));
    
    //after inserted object2 after stackArray[1] (non-included object)
    TENLinkedListInsertObjectAfterObject(list, object2, stackArray[1]);
    
    //it count should not change
    assert(currentCount == TENLinkedListGetCount(list));

    //after remove first object twice
    TENLinkedListRemoveFirstObject(list);
    currentCount -= 1;
    TENLinkedListRemoveFirstObject(list);
    currentCount -= 1;

    //it rootNode->stack should equal object2
    assert(object2 == TENNodeGetStack(TENLinkedListGetRootNode(list)));

    //after inserted NULL before NULL
    TENLinkedListInsertObjectAfterObject(list, NULL, NULL);
    
    //it count should not change
    assert(currentCount == TENLinkedListGetCount(list));
    
    for (int i = 0; i < count; i++) {
        TENRelease(stackArray[i]);
    }
    
    TENRelease(object1);
    TENRelease(object2);
    TENRelease(list);

}


void TENLinkedListEmtyEnumeratorTest() {
    //TENLinkedList
    //after being created
    TENLinkedList *list = TENObjectCreate(TENLinkedList);

    //after being created TENLinkedListEnumerator with list
    TENLinkedListEnumerator *enumerator = TENLinkedListEnumeratorCreateWithList(list);
    
    //enumerator should valid
    assert(TENLinkedListEnumeratorIsValid(enumerator));
    
    //nextObject should equal NULL
    assert(TENLinkedListEnumeratorNextObject(enumerator) == NULL);

    //enumerator should not valid
    assert(!TENLinkedListEnumeratorIsValid(enumerator));
    
    TENRelease(enumerator);
    TENRelease(list);
}

void TENLinkedListEnumeratorTest() {
    //TENLinkedList
    TENLinkedList *list = TENObjectCreate(TENLinkedList);
    
    const uint8_t count = 3;
    TENObject *stackArray[count];
    
    for (int i = 0; i < count; i++) {
        stackArray[i] = TENObjectCreate(TENObject);
        TENLinkedListAddObject(list, stackArray[i]);
    }

    //after being created TENLinkedListEnumerator with list
    TENLinkedListEnumerator *enumerator = TENLinkedListEnumeratorCreateWithList(list);

    //enumerator should valid
    assert(TENLinkedListEnumeratorIsValid(enumerator));
    
    //nextObject should equal stackArray[2]
    assert(TENLinkedListEnumeratorNextObject(enumerator) == stackArray[2]);
    
    //nextObject should equal stackArray[1]
    assert(TENLinkedListEnumeratorNextObject(enumerator) == stackArray[1]);
    
    //enumerator should valid
    assert(TENLinkedListEnumeratorIsValid(enumerator));
    
    //after modifying list application should crash by assert
//    TENLinkedListRemoveFirstObject(list);

    //nextObject should equal stackArray[0]
    assert(TENLinkedListEnumeratorNextObject(enumerator) == stackArray[0]);

    //enumerator should not valid
    assert(!TENLinkedListEnumeratorIsValid(enumerator));

    //nextObject should equal NULL
    assert(TENLinkedListEnumeratorNextObject(enumerator) == NULL);
    
    TENRelease(enumerator);
    
    for (int i = 0; i < count; i++) {
        TENRelease(stackArray[i]);
    }
    
    TENRelease(list);
}

