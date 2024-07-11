#ifndef NLIBC_LINKED_LIST_H
#define NLIBC_LINKED_LIST_H

#include <nlibc/stdtypes.h>


struct linkedList_node;

typedef struct linkedList_head linkedListHead_t;

typedef struct linkedList_head {
    union {
        struct linkedList_node *firstNode;  //the firstNode and begin of the list are the same
        struct linkedList_node *list;
    };
    struct linkedList_node *lastNode;
    uint64_t nodes;

    uint64_t dataSize;

    //* Functions for Data operations
    uint32_t (*data_compare)(void*, void*, linkedListHead_t*); // returns -1 if first "object" is smaller than the second, 0 is theyre eqal and 1 if the second is larger
    void (*data_delete)(void*, linkedListHead_t*);
    void* (*data_copy)(void*, linkedListHead_t*);
    
    //* Memory (de-)allocation functions 
    void* (*memory_allocate)(uint64_t, uint64_t);
    void (*memory_deallocate)(void*);

    //* Callback functions
    void (*callback_onDelete)(void*, linkedListHead_t*, uint64_t);
    void (*callback_onCreate)(void*, linkedListHead_t*, uint64_t);
    void (*callback_onUpdate)(void*, linkedListHead_t*, uint64_t);
    void (*callback_onRetreve)(void*, linkedListHead_t*, uint64_t);
} linkedListHead_t;

typedef struct linkedList_node {
    void* data;

    struct linkedList_node *nextNode;
    struct linkedList_node *prevNode;
    struct linkedList_head *listHead;
} linkedListNode_t;


linkedListHead_t linkedList_createDefault(uint64_t dataSize, uint64_t preallocated_nodes);

linkedListHead_t linkedList_create(uint64_t dataSize, uint64_t preallocated_nodes, void* default_value,
                                    uint32_t (*data_compare)(void*, void*, linkedListHead_t*),
                                    void (*data_delete)(void*, linkedListHead_t*),
                                    void* (*data_copy)(void*, linkedListHead_t*),
                                    void* (*memory_allocate)(uint64_t, uint64_t),
                                    void (*memory_deallocate)(void*),
                                    void (*callback_onDelete)(void*, linkedListHead_t*, uint64_t),
                                    void (*callback_onCreate)(void*, linkedListHead_t*, uint64_t),
                                    void (*callback_onUpdate)(void*, linkedListHead_t*, uint64_t),
                                    void (*callback_onRetreve)(void*, linkedListHead_t*, uint64_t));

void linkedList_delete(linkedListHead_t *head);

void linkedList_append(linkedListHead_t *head, void* data);
void linkedList_prepend(linkedListHead_t *head, void* data);
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

//int64_t linkedList_find(const linkedListHead_t *head, union linkedListTypes data);

//bool linkedList_contains(const linkedListHead_t *head, union linkedListTypes data);

//void linkedList_copy(linkedListHead_t *destenation, const linkedListHead_t *source);

//void linkedList_reverse(linkedListHead_t *head);

//void linkedList_combine(linkedListHead_t *destenation, const linkedListHead_t *source);

//void test_print_ints(linkedListHead_t *head);

#endif