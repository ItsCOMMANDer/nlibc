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
    if(head == NULL) return;
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

//void linkedList_rectify(linkedListHead_t *head);

//void linkedList_append(linkedListHead_t *head, union linkedListTypes data);
//void linkedList_prepend(linkedListHead_t *head, union linkedListTypes data);
//void linkedList_insert(linkedListHead_t *head, uint64_t index, union linkedListTypes data);

//void linkedList_removeLast(linkedListHead_t *head);
//void linkedList_removeFirst(linkedListHead_t *head);
//void linkedList_remove(linkedListHead_t *head, uint64_t index);

//union linkedListTypes linkedList_get(linkedListHead_t *head, uint64_t index);
//union linkedListTypes linkedList_getFirst(linkedListHead_t *head);
//union linkedListTypes linkedList_getLast(linkedListHead_t *head);

//void linkedList_set(const linkedListHead_t *head, uint64_t index, union linkedListTypes data);
//void linkedList_setFirst(const linkedListHead_t *head, union linkedListTypes data);
//void linkedList_setLast(const linkedListHead_t *head, union linkedListTypes data);

//void linkedList_sort(const linkedListHead_t *head);

//uint64_t linkedList_length(const linkedListHead_t *head);

//bool linkedList_isEmpty(const linkedListHead_t *head);

//int64_t linkedList_find(const linkedListHead_t *head, union linkedListTypes data);

//bool linkedList_contains(const linkedListHead_t *head, union linkedListTypes data);

//void linkedList_copy(linkedListHead_t *destenation, const linkedListHead_t *source);

//void linkedList_reverse(linkedListHead_t *head);

//void linkedList_combine(linkedListHead_t *destenation, const linkedListHead_t *source);