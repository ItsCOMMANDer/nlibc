#include "../include/linkedList.h"
#include "../include/memory.h"

void linkedListAppend(linkedListNode_t *listHead, void* data) {
    linkedListNode_t *oldLastNode = listHead->lastNode;
    linkedListNode_t *newLastNode = (linkedListNode_t*)g_mem_allocConfig.mem_alloc(sizeof(linkedListNode_t));
    
    listHead->lastNode = newLastNode;
    listHead->nodes++;

    oldLastNode->nextNode = newLastNode;

    newLastNode->data = data;
    newLastNode->nextNode = NULL;
    newLastNode->prevNode = oldLastNode;
    newLastNode->firstNode = listHead;
    newLastNode->lastNode = newLastNode;
}


void linkedListPrepend(linkedListNode_t *listHead, void* data) {
    linkedListNode_t *oldFirstNode = listHead;
    linkedListNode_t *newFirstNode = (linkedListNode_t*)g_mem_allocConfig.mem_alloc(sizeof(linkedListNode_t));
    
    memcpy(newFirstNode, oldFirstNode, sizeof(linkedListNode_t));

    newFirstNode->data = data;
    newFirstNode->firstNode = newFirstNode;
    newFirstNode->lastNode = oldFirstNode->lastNode;
    newFirstNode->nextNode = oldFirstNode;
    newFirstNode->nodes++;
    newFirstNode->prevNode = NULL;

    oldFirstNode->firstNode = newFirstNode;
    oldFirstNode->prevNode = newFirstNode;
}

void linkedListInsert(linkedListNode_t *listHead, void* data, uint64_t index) {
    linkedListNode_t *node = listHead;
    for(int i = 0; i < index - 1; i++) node = node->nextNode;

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