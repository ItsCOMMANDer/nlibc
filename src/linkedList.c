#include "../include/linkedList.h"
#include "../include/memory.h"

linkedListNode_t *linkedListCreateEmpty(uint64_t nodes, union linkedListTypes startingData) {
    linkedListNode_t *linkedList = memoryClearedMalloc(sizeof(linkedListNode_t), nodes);
    struct linkedList_metaData *metaData = memoryAlloc(sizeof(struct linkedList_metaData));
    
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

    return &linkedList[0];
}

void linkedListAppend(const linkedListNode_t *listHead, union linkedListTypes data) {
    linkedListNode_t *newLastNode = memoryClearedMalloc(sizeof(linkedListNode_t), 1);
    linkedListNode_t *oldLastNode = listHead->metaData->lastNode;

    oldLastNode->nextNode = newLastNode;

    newLastNode->prevNode = oldLastNode;
    newLastNode->nextNode = NULL;
    newLastNode->data = data;
    newLastNode->metaData = listHead->metaData;

    listHead->metaData->lastNode = newLastNode;
}


void linkedListPrepend(linkedListNode_t *listHead, union linkedListTypes data) {
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

union linkedListTypes linkedListGetValue(linkedListNode_t *listHead, uint64_t index) {
    linkedListNode_t *linkedList = listHead;

    for(int i = 0; i < index; i++) {
        linkedList = linkedList->nextNode;
    }

    return linkedList->data;
}

linkedListNode_t linkedListClone(const linkedListNode_t *listHead) {
    linkedListNode_t *newList = memoryClearedMalloc(sizeof(linkedListNode_t), listHead->metaData->nodes);

    struct linkedList_metaData *newMetaData = memoryClearedMalloc(sizeof(struct linkedList_metaData), 1);

    memoryCopy(newMetaData, newList->metaData, sizeof(struct linkedList_metaData));
    newMetaData->firstNode = newList;
    newMetaData->lastNode = &newList[listHead->metaData->nodes - 1];

    linkedListNode_t currentNode = *listHead;

    uint64_t index = 0;

    while(currentNode.nextNode != NULL) {

        memoryCopy(&newList[index], &currentNode, sizeof(linkedListNode_t));
        newList[index].metaData = newMetaData;

        currentNode = *currentNode.nextNode;
    }

    for(index = 0; index < newList->metaData->nodes - 1; index++) {newList[index].nextNode = &newList[index + 1];}
    for(index = newList->metaData->nodes - 1; index > 0; index--) {newList[index].prevNode = &newList[index - 1];}

    return newList[0];
}

uint64_t linkedListLength(linkedListNode_t listHead) {
    return listHead.metaData->nodes;
}

/*


linkedListNode_t linkedListSubList(linkedListNode_t listHead, uint64_t listStart, uint64_t listEnd);


void** linkedListToArray(linkedListNode_t listHead);

void* linkedListReduce(linkedListNode_t listHead, void* (*reduceFunc)(void*, void*));

*/


void  linkedListDelete(linkedListNode_t *listHead) {
    linkedListNode_t *currentNode = listHead->metaData->lastNode;
    if(listHead->metaData->deleteData == NULL) {
        while(currentNode != NULL) {
            currentNode = currentNode->prevNode;
            memoryFree(currentNode->nextNode);
        }
    } else {
        while(currentNode != NULL) {
            currentNode = currentNode->prevNode;
            listHead->metaData->deleteData(currentNode->nextNode->data);
            memoryFree(currentNode->nextNode);
        }
    }
}
