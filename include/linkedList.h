#ifndef MYSTD_LINKED_LIST_H
#define MYSTD_LINKED_LIST_H

#include "stdtypes.h"

struct linkedList_node;

struct linkedList_metaData {
    struct linkedList_node *firstNode;
    struct linkedList_node *lastNode;
    uint64_t nodes;
};

typedef struct linkedList_node {
    void *data;
    struct linkedList_node *nextNode;
    struct linkedList_node *prevNode;
    struct linkedList_metaData *metaData;
} linkedListNode_t;

linkedListNode_t linkedListCreateEmpty(uint64_t nodes, void* startingData);

void linkedListAppend(const linkedListNode_t *listHead, void* data);
void linkedListPrepend(linkedListNode_t *listHead, void* data);

void* linkedListGetValue(linkedListNode_t *listHead, uint64_t index);

linkedListNode_t linkedListClone(const linkedListNode_t *listHead);

//linkedListNode_t linkedListSubList(linkedListNode_t listHead, uint64_t listStart, uint64_t listEnd);

void linkedListDelete(linkedListNode_t *listHead);

linkedListNode_t linkedListCreateEmptyList(uint64_t amountOfEntries);

uint64_t linkedListLength(linkedListNode_t listHead);

//void** linkedListToArray(linkedListNode_t listHead);

//void* linkedListReduce(linkedListNode_t listHead, void* (*reduceFunc)(void*, void*));

#endif