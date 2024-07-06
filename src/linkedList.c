#include "../include/linkedList.h"
#include "../include/memory.h"

void linkedList_delete(linkedListHead_t *head) {
    if(head == NULL) return;
    if(head->data_delete == NULL) {
        linkedListNode_t *current_node = head->firstNode;
        while(current_node->nextNode != NULL) {
            linkedListNode_t *next_node = current_node->nextNode;
            head->memoryFree(current_node);
            current_node = next_node;
        }
    } else {
        linkedListNode_t *current_node = head->firstNode;
        while(current_node->nextNode != NULL) {
            linkedListNode_t *next_node = current_node->nextNode;
            head->memoryFreeData(current_node->data);
            head->memoryFree(current_node);
            current_node = next_node;
        }
    }
}

bool linkedList_validate(const linkedListHead_t *head) {
    if(head == NULL) return false;
    if((head->firstNode->prevNode != NULL) || head->lastNode->nextNode != NULL) return false;
    
    linkedListNode_t *current_node = head->firstNode;
    uint64_t nodes = 0;
    while(current_node->nextNode != NULL) {
        nodes++;
        current_node = current_node->nextNode;
    }

    if(nodes != head->nodes) return false;
    
    if(head->data_validate == NULL) return true;

    current_node = head->firstNode;
    while(current_node->nextNode != NULL) {
        if(!head->data_validate(current_node->data)) return false;
        current_node = current_node->nextNode;
    }

    return true;
}

void linkedList_rectify(linkedListHead_t *head) {
    if(linkedList_validate(head)) return;

    linkedListNode_t *current_node = head->list;

    while(current_node->prevNode != NULL) {
        current_node = current_node->prevNode;
    }

    head->firstNode = current_node;

    while(current_node->nextNode != NULL) {
        if(!head->data_validate(current_node->data)) head->data_rectify(current_node->data);
        current_node = current_node->nextNode;
    }

    head->lastNode = current_node;

    return;
}

void linkedList_append(linkedListHead_t *head, union linkedListTypes data) {
    if(head == NULL) return;
    if(head->memoryAllocate == NULL) return;

    linkedListNode_t *newNode = head->memoryAllocate(1,  sizeof(linkedListNode_t));
    newNode->data = data;
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

    head->nodes++;

    return;
}

void linkedList_prepend(linkedListHead_t *head, union linkedListTypes data) {
    if(head == NULL) return;
    if(head->memoryAllocate == NULL) return;

    linkedListNode_t *newNode = head->memoryAllocate(1, sizeof(linkedListNode_t));

    newNode->data = data;
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

    head->nodes++;

    return;
}

void linkedList_insert(linkedListHead_t *head, uint64_t index, union linkedListTypes data) {
    if(head == NULL) return;
    if(head->memoryAllocate == NULL) return;

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


    linkedListNode_t *newNode = head->memoryAllocate(1, sizeof(linkedListNode_t));

    newNode->data = data;
    newNode->listHead = head;
    newNode->nextNode = currentNode;
    newNode->prevNode = currentNode->prevNode;

    newNode->prevNode->nextNode = newNode;

    currentNode->prevNode = newNode;

    head->nodes++;

    
    return;
}

void linkedList_removeLast(linkedListHead_t *head) {
    if(head == NULL) return;
    if(head->memoryFree == NULL) return;

    if(head->nodes == 0) return;

    if(head->memoryFreeData != NULL) {head->memoryFreeData(head->lastNode->data);}

    if(head->nodes == 1) {
        head->memoryFree(head->lastNode);
        head->lastNode = NULL;
        head->firstNode = NULL;
        head->nodes--;
        return;
    }

    head->lastNode->prevNode->nextNode = NULL;

    linkedListNode_t *old_node = head->lastNode;

    head->lastNode = head->lastNode->prevNode;

    head->memoryFree(old_node);

    head->nodes--;
    
    return;
}

void linkedList_removeFirst(linkedListHead_t *head) {
    if(head == NULL) return;
    if(head->memoryFree == NULL) return;

    if(head->nodes == 0) return;

    if(head->memoryFreeData != NULL) {head->memoryFreeData(head->lastNode->data);}

    if(head->nodes == 1) {
        head->memoryFree(head->lastNode);
        head->lastNode = NULL;
        head->firstNode = NULL;
        head->nodes--;
        return;
    }

    head->firstNode->nextNode->prevNode = NULL;

    linkedListNode_t *old_node = head->firstNode;

    head->firstNode = head->firstNode->nextNode;

    head->memoryFree(old_node);

    head->nodes--;

    return;

}

void linkedList_remove(linkedListHead_t *head, uint64_t index) {
    if(head == NULL) return;
    if(head->memoryFree == NULL) return;

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

    if(head->memoryFreeData != NULL) {
        head->memoryFreeData(currentNode->data);
    }

    head->memoryFree(currentNode);

    head->nodes--;

    return;
}

union linkedListTypes linkedList_get(linkedListHead_t *head, uint64_t index) {
    if(head == NULL) return;  // FIX THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    linkedListNode_t *currentNode = head->firstNode;

    for(uint64_t i = 0; i < index; i++) {
        currentNode = currentNode->nextNode;
        if(currentNode->nextNode == NULL) break;
    }

    return currentNode->data;
}

union linkedListTypes linkedList_getFirst(linkedListHead_t *head) {
    if(head == NULL) return;            //FIX THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return head->firstNode->data;
}

union linkedListTypes linkedList_getLast(linkedListHead_t *head) {
    if(head == NULL) return;            //FIX THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return head->lastNode->data;
}

void linkedList_set(const linkedListHead_t *head, uint64_t index, union linkedListTypes data) {
    if(head == NULL) return;            //FIX THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    linkedListNode_t *currentNode = head->firstNode;

    for(uint64_t i = 0; i < index; i++) {
        currentNode = currentNode->nextNode;
        if(currentNode->nextNode == NULL) break;
    }

    currentNode->data = data;

    return;
}

void linkedList_setFirst(const linkedListHead_t *head, union linkedListTypes data) {
    if(head == NULL) return;
    head->firstNode->data = data;

    return;
}

void linkedList_setLast(const linkedListHead_t *head, union linkedListTypes data) {
    if(head == NULL) return;
    head->lastNode->data = data;

    return;
}

//void linkedList_sort(const linkedListHead_t *head);

uint64_t linkedList_length(const linkedListHead_t *head) {
    if(head == NULL) return;    //FIX THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return head->nodes;
}

bool linkedList_isEmpty(const linkedListHead_t *head) {
    if(head == NULL) return true; //?????????????????
    return (head->nodes == 0);
}

//int64_t linkedList_find(const linkedListHead_t *head, union linkedListTypes data);

//bool linkedList_contains(const linkedListHead_t *head, union linkedListTypes data);

//void linkedList_copy(linkedListHead_t *destenation, const linkedListHead_t *source);

void linkedList_reverse(linkedListHead_t *head) {
    if (head == NULL) return;
    if(head->nodes == NULL) return;

    linkedListNode_t *frontNode = head->firstNode;
    linkedListNode_t *backNode = head->lastNode;

    while (frontNode != backNode && frontNode->prevNode != backNode) {
        union linkedListTypes swap;
        swap = frontNode->data;
        frontNode->data = backNode->data;
        backNode->data = swap;

        frontNode = frontNode->nextNode;
        backNode = backNode->prevNode;
    }

    return;
}

//void linkedList_combine(linkedListHead_t *destenation, const linkedListHead_t *source);


#include <stdio.h>

void test_print_ints(linkedListHead_t *head) {
    if(head->nodes == 0) {
        printf("LEER\n");
        return;
    }
    linkedListNode_t *current = head->firstNode;
    while(current->nextNode != NULL) {
        printf("%i ", current->data.int_t);
        if(current->nextNode != NULL) {printf("-> ");}
        current = current->nextNode;
    }
    printf("%i\n", current->data.int_t);
}