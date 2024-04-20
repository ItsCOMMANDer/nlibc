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

    linkedList[nodes - 1].nextNode = NULL;
    linkedList[0].prevNode = NULL;

    return linkedList[0];
}

void linkedListAppend(const linkedListNode_t *listHead, void* data) {
    linkedListNode_t *newLastNode = memoryClearedMalloc(sizeof(linkedListNode_t), 1);
    linkedListNode_t *oldLastNode = listHead->metaData->lastNode;

    oldLastNode->nextNode = newLastNode;

    newLastNode->prevNode = oldLastNode;
    newLastNode->nextNode = NULL;
    newLastNode->data = data;
    newLastNode->metaData = listHead->metaData;

    listHead->metaData->lastNode = newLastNode;
}


void linkedListPrepend(linkedListNode_t *listHead, void* data) {
    linkedListNode_t *newFirstNode = memoryClearedMalloc(sizeof(linkedListNode_t), 1);
    linkedListNode_t *oldFirstNode = listHead->metaData->firstNode;

    memoryCopy(oldFirstNode, newFirstNode, sizeof(linkedListNode_t));
    oldFirstNode->prevNode = newFirstNode;

    newFirstNode->prevNode = NULL;
    newFirstNode->nextNode = oldFirstNode;
    newFirstNode->data = data;
    newFirstNode->metaData = listHead->metaData;

    listHead->metaData->firstNode = newFirstNode;
}

void* linkedListGetValue(linkedListNode_t *listHead, uint64_t index) {
    linkedListNode_t *linkedList = listHead;

    for(int i = 0; i < index; i++) {
        linkedList = linkedList->nextNode;
    }

    return linkedList->data;
}

/*


linkedListNode_t linkedListSplit(linkedListNode_t listHead, uint64_t index);
linkedListNode_t linkedListConnect(int count, ...);

linkedListNode_t linkedListClone(linkedListNode_t listHead);

linkedListNode_t linkedListSubList(linkedListNode_t listHead, uint64_t listStart, uint64_t listEnd);

linkedListNode_t linkedListDelete(linkedListNode_t listHead);

linkedListNode_t linkedListCreateEmptyList(uint64_t amountOfEntries);

uint64_t linkedListLength(linkedListNode_t listHead);

void** linkedListToArray(linkedListNode_t listHead);

void* linkedListReduce(linkedListNode_t listHead, void* (*reduceFunc)(void*, void*));

*/