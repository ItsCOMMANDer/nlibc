#include <nlibc/linkedList.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void linkedList_delete(linkedListHead_t *head) {
    if(head == NULL) return;
    linkedListNode_t *currentNode = head->firstNode;
    while(currentNode->nextNode != NULL) {
        linkedListNode_t *nextNode = currentNode->nextNode;
        head->memory_deallocate(currentNode);
        currentNode = nextNode;
    }
}


void linkedList_append(linkedListHead_t *head, void* data) {
    if(head == NULL) return;
    if(head->memory_allocate == NULL) return;

    linkedListNode_t *newNode = head->memory_allocate(1,  sizeof(linkedListNode_t) + head->dataSize);
    

    newNode->listHead = head;
    newNode->nextNode = NULL;
    newNode->prevNode = head->lastNode;

    if(head->nodes != 0) {
        head->lastNode->nextNode = newNode;
        head->lastNode = newNode;
    } else {
        head->lastNode = newNode;
        head->firstNode = newNode;
    }

    if(data != NULL) {
        memcpy(newNode->data, data, head->dataSize);
    } else {
        memset(newNode->data, 0, head->dataSize);
    }

    head->nodes++;

    return;
}

void linkedList_prepend(linkedListHead_t *head, void* data) {
    if(head == NULL) return;
    if(head->memory_allocate == NULL) return;

    linkedListNode_t *newNode = head->memory_allocate(1, sizeof(linkedListNode_t));

    newNode->listHead = head;
    newNode->nextNode = head->firstNode;
    newNode->prevNode = NULL;

    if(head->nodes != 0) {
        head->firstNode->prevNode = newNode;
        head->firstNode = newNode;
    } else {
        head->firstNode = newNode;
        head->lastNode = newNode;
    }

    if(data != NULL) {
        memcpy(newNode->data, data, head->dataSize);
    } else {
        memset(newNode->data, 0, head->dataSize);
    }

    head->nodes++;

    return;
}

void linkedList_insert(linkedListHead_t *head, uint64_t index, void* data) {
    if(head == NULL) return;
    if(head->memory_allocate == NULL) return;

    if(index == 0) {
        linkedList_prepend(head, data);
        return;
    }
    if(index > head->nodes) {
        linkedList_append(head, data);
        return;
    }


    linkedListNode_t *currentNode = head->firstNode;

    for(uint64_t i = 0; i < index; i++) {
        currentNode = currentNode->nextNode;
    }


    linkedListNode_t *newNode = head->memory_allocate(1, sizeof(linkedListNode_t) + head->dataSize);

    memcpy(newNode->data, data, head->dataSize);
    newNode->listHead = head;
    newNode->nextNode = currentNode;
    newNode->prevNode = currentNode->prevNode;

    newNode->prevNode->nextNode = newNode;

    currentNode->prevNode = newNode;

    if(data != NULL) {
        memcpy(newNode->data, data, head->dataSize);
    } else {
        memset(newNode->data, 0, head->dataSize);
    }

    head->nodes++;
    
    return;
}

void linkedList_removeLast(linkedListHead_t *head) {
    if(head == NULL) return;
    if(head->memory_deallocate == NULL) return;

    if(head->nodes == 0) return;

    if(head->nodes == 1) {
        head->memory_deallocate(head->lastNode);
        head->lastNode = NULL;
        head->firstNode = NULL;
        head->nodes = 0;
        return;
    }

    head->lastNode->prevNode->nextNode = NULL;

    linkedListNode_t *old_node = head->lastNode;

    head->lastNode = head->lastNode->prevNode;

    head->memory_deallocate(old_node);

    head->nodes--;
    
    return;
}


void linkedList_removeFirst(linkedListHead_t *head) {
    if(head == NULL) return;
    if(head->memory_deallocate == NULL) return;

    if(head->nodes == 0) return;

    if(head->nodes == 1) {
        head->memory_deallocate(head->lastNode);
        head->lastNode = NULL;
        head->firstNode = NULL;
        head->nodes--;
        return;
    }

    head->firstNode->nextNode->prevNode = NULL;

    linkedListNode_t *old_node = head->firstNode;

    head->firstNode = head->firstNode->nextNode;

    head->memory_deallocate(old_node);

    head->nodes--;

    return;
}

void linkedList_remove(linkedListHead_t *head, uint64_t index) {
    if(head == NULL) return;
    if(head->memory_deallocate == NULL) return;

    if(index == 0) {
        linkedList_removeFirst(head);
        return;
    }

    if(index == head->nodes - 1) {
        linkedList_removeLast(head);
        return;
    }

    linkedListNode_t *currentNode = head->firstNode;

    for(uint64_t i = 0; i < index; i++) {
        currentNode = currentNode->nextNode;
    }

    currentNode->prevNode->nextNode = currentNode->nextNode;
    currentNode->nextNode->prevNode = currentNode->prevNode;

    head->memory_deallocate(currentNode);

    head->nodes--;

    return;
}

void* linkedList_get(linkedListHead_t *head, uint64_t index) {
    if(head == NULL) return NULL;
    linkedListNode_t *currentNode = head->firstNode;

    for(uint64_t i = 0; i < index; i++) {
        currentNode = currentNode->nextNode;
        if(currentNode->nextNode == NULL) return NULL;
    }

    return &currentNode->data;
}

void* linkedList_getFirst(linkedListHead_t *head) {
    if(head == NULL) return NULL;
    return &head->firstNode->data;
}

void* linkedList_getLast(linkedListHead_t *head) {
    if(head == NULL) return NULL;
    return &head->firstNode->data;
}


void linkedList_set(const linkedListHead_t *head, uint64_t index, void* src) {
    if(head == NULL || src == NULL) return; //TODO: Error handling
    linkedListNode_t *currentNode = head->firstNode;

    for(uint64_t i = 0; i < index; i++) {
        currentNode = currentNode->nextNode;
        if(currentNode->nextNode == NULL) return; //TODO: Error handling
    }
    
    memcpy(currentNode->data, src, head->dataSize);

    return;
}

void linkedList_setFirst(const linkedListHead_t *head, void* src) {
    if(head == NULL || src == NULL) return; //TODO: Error handling

    memcpy(head->firstNode->data, src, head->dataSize);

    return;
}

void linkedList_setLast(const linkedListHead_t *head, void* src) {
    if(head == NULL || src == NULL) return; //TODO: Error handling

    memcpy(head->lastNode->data, src, head->dataSize);

    return;
}

uint64_t partition(linkedListHead_t *head, uint64_t low, uint64_t high) {
    void* pivot = linkedList_get(head, low);
    uint64_t i = low;
    uint64_t j = high;

    void* tmpData = malloc(head->dataSize);

    while(i < j) {
        while((head->data_compare(linkedList_get(head, i), pivot, head) != 1) && (i <= high - 1)) {i++;}
        
        while((head->data_compare(linkedList_get(head, j), pivot) == 1) && (j >= low + 1)) {j--;}

        if (i < j) {
            void* iData = linkedList_get(head, i);
            void* jData = linkedList_get(head, j);

            memcpy(tmpData, iData, head->dataSize);
            memcpy(iData, jData, head->dataSize);
            memcpy(jData, tmpData, head->dataSize);
            
        }
    }


    void* lowData = linkedList_get(head, low);
    void* jData = linkedList_get(head, j);

    memcpy(tmpData, lowData, head->dataSize);
    memcpy(lowData, jData, head->dataSize);
    memcpy(jData, tmpData, head->dataSize);
            
    free(tmpData);

    swap(&arr[low], &arr[j]);
    return j;
}

void linkedListInternal_sort(linkedListHead_t *head, uint64_t low, uint64_t high) {
    if(low < high) {
        uint64_t partitionIndex = partition(head, low, high);

        quickSort(head, low, partitionIndex - 1);
        quickSort(head, partitionIndex + 1, high);
    }
}


void linkedList_qsort(const linkedListHead_t *head) {
    return;
}

uint64_t linkedList_length(const linkedListHead_t *head) {
    if(head == NULL) return 0; //TODO: Error handling
    return head->nodes;
}



bool linkedList_isEmpty(const linkedListHead_t *head) {
    if(head == NULL) return true;
    return head->nodes == 0;
}

//int64_t linkedList_find(const linkedListHead_t *head, union linkedListTypes data);

bool linkedList_contains(const linkedListHead_t *head, void *data) {
    if(head == NULL || data == NULL) return false;

    linkedListNode_t *currentNode = head->firstNode;

    if(currentNode == NULL) return false;

    while(currentNode->nextNode != NULL) {
        if(head->data_compare(data, currentNode->data, head) == 0) return true;
        currentNode = currentNode->nextNode;
    }

    return false;
}

//void linkedList_copy(linkedListHead_t *destenation, const linkedListHead_t *source);

void linkedList_reverse(linkedListHead_t *head) {
    if (head == NULL) return;
    if(head->nodes == 0) return;

    linkedListNode_t *frontNode = head->firstNode;
    linkedListNode_t *backNode = head->lastNode;

    void* swap = malloc(head->dataSize);
    while (frontNode != backNode && frontNode->prevNode != backNode) {
        memcpy(swap, frontNode->data, head->dataSize);

        memcpy(frontNode->data, backNode->data, head->dataSize);

        memcpy(backNode->data, swap, head->dataSize);

        frontNode = frontNode->nextNode;
        backNode = backNode->prevNode;
    }
    free(swap);

    return;
}

//void linkedList_combine(linkedListHead_t *destenation, const linkedListHead_t *source);