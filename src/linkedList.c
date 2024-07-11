#include <nlibc/linkedList.h>
#include <nlibc/memory.h> 

//linkedListHead_t linkedList_createDefault(uint64_t dataSize, uint64_t preallocated_nodes) {}

linkedListHead_t linkedList_create(uint64_t dataSize, uint64_t preallocated_nodes, void* default_value,
                                    uint32_t (*data_compare)(void*, void*, linkedListHead_t*),
                                    void (*data_delete)(void*, linkedListHead_t*),
                                    void* (*data_copy)(void*, linkedListHead_t*),
                                    void* (*memory_allocate)(uint64_t, uint64_t),
                                    void (*memory_deallocate)(void*),
                                    void (*callback_onDelete)(void*, linkedListHead_t*, uint64_t),
                                    void (*callback_onCreate)(void*, linkedListHead_t*, uint64_t),
                                    void (*callback_onUpdate)(void*, linkedListHead_t*, uint64_t),
                                    void (*callback_onRetreve)(void*, linkedListHead_t*, uint64_t)) {
    linkedListHead_t newhead = {
        .firstNode = NULL,
        .list = NULL,
        .lastNode = NULL,
        .nodes = 0,
        .dataSize = dataSize,
        .data_compare = data_compare,
        .data_delete = data_delete,
        .data_copy = data_copy,
        .memory_allocate = memory_allocate,
        .memory_deallocate = memory_deallocate,
        .callback_onDelete = callback_onDelete,
        .callback_onCreate = callback_onCreate,
        .callback_onUpdate = callback_onUpdate,
        .callback_onRetreve = callback_onRetreve,
    };
}

void linkedList_delete(linkedListHead_t *head) {
    if(head == NULL) return;
    linkedListNode_t *current_node = head->firstNode;
    uint64_t index = 0;
    while(current_node->nextNode != NULL) {
        linkedListNode_t *next_node = current_node->nextNode;
        if(head->callback_onDelete != NULL) head->callback_onDelete(current_node->data, head, index++);
        head->data_delete(current_node->data, head);
        head->memory_deallocate(current_node);
        current_node = next_node;
    }
}


void linkedList_append(linkedListHead_t *head, void* data) {
    if(head == NULL) return;
    if(head->memory_allocate == NULL) return;

    linkedListNode_t *newNode = head->memory_allocate(1,  sizeof(linkedListNode_t));
    

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
        newNode->data = head->memory_allocate(1, head->dataSize);
        memory_copy(newNode->data, data, head->dataSize);
        if(head->callback_onCreate != NULL) head->callback_onCreate(newNode->data, head, ++head->nodes);
        return;
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
        newNode->data = head->memory_allocate(1, head->dataSize);
        memory_copy(newNode->data, data, head->dataSize);
        if(head->callback_onCreate != NULL) head->callback_onCreate(newNode->data, head, ++head->nodes);
        return;
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


    linkedListNode_t *newNode = head->memory_allocate(1, sizeof(linkedListNode_t));

    newNode->data = data;
    newNode->listHead = head;
    newNode->nextNode = currentNode;
    newNode->prevNode = currentNode->prevNode;

    newNode->prevNode->nextNode = newNode;

    currentNode->prevNode = newNode;

    if(data != NULL) {
        newNode->data = head->memory_allocate(1, head->dataSize);
        memory_copy(newNode->data, data, head->dataSize);
        if(head->callback_onCreate != NULL) head->callback_onCreate(newNode->data, head, ++head->nodes);
        return;
    }

    head->nodes++;
    
    return;
}

void linkedList_removeLast(linkedListHead_t *head) {
    if(head == NULL) return;
    if(head->memory_deallocate == NULL) return;

    if(head->nodes == 0) return;

    if(head->callback_onDelete != NULL) head->callback_onDelete(head->lastNode->data, head, head->nodes - 1);
    if(head->memory_deallocate != NULL && head->lastNode->data != NULL) {head->memory_deallocate(head->lastNode->data);}

    if(head->nodes == 1) {
        head->memory_deallocate(head->lastNode);
        head->lastNode = NULL;
        head->firstNode = NULL;
        head->nodes--;
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

    if(head->callback_onDelete != NULL) head->callback_onDelete(head->firstNode->data, head, 0);
    if(head->memory_deallocate != NULL && head->lastNode->data != NULL) head->memory_deallocate(head->lastNode->data);

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

    if(head->callback_onDelete != NULL) head->callback_onDelete(currentNode->data, head, index);
    if(head->memory_deallocate != NULL && currentNode->data != NULL) head->memory_deallocate(currentNode->data);

    head->memory_deallocate(currentNode);

    head->nodes--;

    return;
}

void linkedList_get(linkedListHead_t *head, void* dest, uint64_t index) {
    if(head == NULL || dest == NULL) return;  // FIX THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    linkedListNode_t *currentNode = head->firstNode;

    for(uint64_t i = 0; i < index; i++) {
        currentNode = currentNode->nextNode;
        if(currentNode->nextNode == NULL) break;
    }

    if(head->callback_onRetreve != NULL) head->callback_onRetreve(currentNode->data, head, index);
    memory_copy(dest, currentNode->data, head->dataSize);

    return;
}

void linkedList_getFirst(linkedListHead_t *head, void* dest) {
    if(head == NULL || dest == NULL) return;            //FIX THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(head->callback_onRetreve != NULL) head->callback_onRetreve(head->firstNode->data, head, 0);
    memory_copy(dest, head->firstNode->data, head->dataSize);
}

void linkedList_getLast(linkedListHead_t *head, void* dest) {
    if(head == NULL || dest == NULL) return;            //FIX THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(head->callback_onRetreve != NULL) head->callback_onRetreve(head->lastNode->data, head, head->nodes - 1);
    memory_copy(dest, head->lastNode->data, head->dataSize);
}


void linkedList_set(const linkedListHead_t *head, uint64_t index, void* src) {
    if(head == NULL || src == NULL) return;            //FIX THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    linkedListNode_t *currentNode = head->firstNode;

    for(uint64_t i = 0; i < index; i++) {
        currentNode = currentNode->nextNode;
        if(currentNode->nextNode == NULL) break;
    }

    memory_copy(currentNode->data, src, head->dataSize);
    if(head->callback_onUpdate != NULL) head->callback_onUpdate(currentNode->data, head, index);

    return;
}

void linkedList_setFirst(const linkedListHead_t *head, void* src) {
    if(head == NULL || src == NULL) return;
    
    memory_copy(head->firstNode->data, src, head->dataSize);
    if(head->callback_onUpdate != NULL) head->callback_onUpdate(head->firstNode->data, head, 0);

    return;
}

void linkedList_setLast(const linkedListHead_t *head, void* src) {
    if(head == NULL || src == NULL) return;

    memory_copy(head->lastNode->data, src, head->dataSize);
    if(head->callback_onUpdate != NULL) head->callback_onUpdate(head->lastNode->data, head, head->nodes - 1);

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
        void* swap;
        swap = frontNode->data;
        frontNode->data = backNode->data;
        backNode->data = swap;

        frontNode = frontNode->nextNode;
        backNode = backNode->prevNode;
    }

    return;
}

//void linkedList_combine(linkedListHead_t *destenation, const linkedListHead_t *source);