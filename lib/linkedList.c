#include "../include/linkedList.h"
#include "../include/memory.h"

linkedListNode_t linkedListCreateEmpty(uint64_t nodes, void* startingData) {
    linkedListNode_t *linkedList = memoryClearedMalloc(sizeof(linkedListNode_t), nodes);
    struct linkedList_metaData *metaData = g_mem_allocConfig.mem_alloc(sizeof(struct linkedList_metaData));
    
    metaData->nodes = nodes;
    metaData->firstNode = &linkedList[0];
    metaData->lastNode = &linkedList[nodes - 1];

    for(uint64_t index = 0; index < nodes - 1; index++) {linkedList[index].nextNode = &linkedList[index + 1];}
    for(uint64_t index = nodes - 1; index > 0; index--) {linkedList[index].prevNode = &linkedList[index - 1];}

    for(uint64_t index = 0; index < nodes; index++) {
        linkedList[index].data = startingData;
        linkedList[index].metaData = metaData;
    }
    return linkedList[0];
}

void linkedListAppend(linkedListNode_t *listHead, void* data) {
    
}


void linkedListPrepend(linkedListNode_t *listHead, void* data) {
    
}

void linkedListInsert(linkedListNode_t *listHead, void* data, uint64_t index) {
    

}


linkedListNode_t linkedListRemove(linkedListNode_t listHead, uint64_t index);

void* linkedListGetValue(linkedListNode_t listHead, uint64_t index);

linkedListNode_t linkedListSplit(linkedListNode_t listHead, uint64_t index);
linkedListNode_t linkedListConnect(int count, ...);

linkedListNode_t linkedListClone(linkedListNode_t listHead);

linkedListNode_t linkedListSubList(linkedListNode_t listHead, uint64_t listStart, uint64_t listEnd);

linkedListNode_t linkedListDelete(linkedListNode_t listHead);

linkedListNode_t linkedListCreateEmptyList(uint64_t amountOfEntries);

uint64_t linkedListLength(linkedListNode_t listHead);

void** linkedListToArray(linkedListNode_t listHead);

void* linkedListReduce(linkedListNode_t listHead, void* (*reduceFunc)(void*, void*));