#ifndef MYSTD_LINKED_LIST_H
#define MYSTD_LINKED_LIST_H

#include "stdtypes.h"

union linkedListTypes {
    char char_t;
    short short_t;
    int int_t;
    long long_t;
    float float_t;
    _Bool bool_t;
    double double_t;
    long long longlong_t;
    void* ptr_t;

    //_Decimal32 decimal32_t;
    //_Decimal64 decimal64_t;       //idk, doesnt work with this for some reason
    //_Decimal128 decimal128_t;
};

struct linkedList_node;

struct linkedList_metaData {
    struct linkedList_node *firstNode;
    struct linkedList_node *lastNode;
    uint64_t nodes;

    void (*deleteData)(union linkedListTypes);
};

typedef struct linkedList_node {
    union linkedListTypes data;
    struct linkedList_node *nextNode;
    struct linkedList_node *prevNode;
    struct linkedList_metaData *metaData;
} linkedListNode_t;

linkedListNode_t *linkedListCreateEmpty(uint64_t nodes, union linkedListTypes startingData);

void linkedListAppend(const linkedListNode_t *listHead, union linkedListTypes data);
void linkedListPrepend(linkedListNode_t *listHead, union linkedListTypes data);

union linkedListTypes linkedListGetValue(linkedListNode_t *listHead, uint64_t index);

linkedListNode_t linkedListClone(const linkedListNode_t *listHead);

//linkedListNode_t linkedListSubList(linkedListNode_t listHead, uint64_t listStart, uint64_t listEnd);

void  linkedListDelete(linkedListNode_t *listHead);

linkedListNode_t linkedListCreateEmptyList(uint64_t amountOfEntries);

uint64_t linkedListLength(linkedListNode_t listHead);

//void** linkedListToArray(linkedListNode_t listHead);

//void* linkedListReduce(linkedListNode_t listHead, void* (*reduceFunc)(void*, void*));

#endif