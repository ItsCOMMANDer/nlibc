#ifndef NLIBC_LINKED_LIST_H
#define NLIBC_LINKED_LIST_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

struct linkedList_node;

typedef struct linkedList_head linkedListHead_t;

typedef struct linkedList_head {
    union {
        struct linkedList_node *firstNode;  //the firstNode and begin of the list are the same
        struct linkedList_node *list;
    };
    struct linkedList_node *lastNode;
    int64_t nodes;

    size_t dataSize;

    //* Functions for Data operations
    int32_t (*data_compare)(void*, void*, const linkedListHead_t*); // returns -1 if first "object" is smaller than the second, 0 is theyre eqal and 1 if the first is larger
    
    //void (*data_delete)(void*, linkedListHead_t*);
    //void* (*data_copy)(void*, linkedListHead_t*);
    
    //* Memory (de-)allocation functions 
    void* (*memory_allocate)(uint64_t);
    void (*memory_deallocate)(void*);
} linkedListHead_t;

typedef struct linkedList_node {
    struct linkedList_node *nextNode;
    struct linkedList_node *prevNode;
    struct linkedList_head *listHead;
    
    char data[];
} linkedListNode_t;

#include <nlibc/linkedList.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

linkedListHead_t linkedList_create(uint64_t dataSize, int32_t (*compare)(void*, void*, const linkedListHead_t*));
void linkedList_delete(linkedListHead_t *head);

void linkedList_append(linkedListHead_t *head, void* data);
void linkedList_prepend(linkedListHead_t *head, void* data);
void linkedList_insert(linkedListHead_t *head, int64_t index, void* data);

void linkedList_removeLast(linkedListHead_t *head);
void linkedList_removeFirst(linkedListHead_t *head);
void linkedList_remove(linkedListHead_t *head, int64_t index);

void* linkedList_get(linkedListHead_t *head, int64_t index);
void* linkedList_getFirst(linkedListHead_t *head);
void* linkedList_getLast(linkedListHead_t *head);

void linkedList_set(const linkedListHead_t *head, int64_t index, void* src);
void linkedList_setFirst(const linkedListHead_t *head, void* src);
void linkedList_setLast(const linkedListHead_t *head, void* src);

void linkedList_qsort(linkedListHead_t *head);

int64_t linkedList_length(const linkedListHead_t *head);

bool linkedList_isEmpty(const linkedListHead_t *head);

//int64_t linkedList_find(const linkedListHead_t *head, union linkedListTypes data);

bool linkedList_contains(const linkedListHead_t *head, void *data);

//void linkedList_copy(linkedListHead_t *destenation, const linkedListHead_t *source);

void linkedList_reverse(linkedListHead_t *head);

//void linkedList_combine(linkedListHead_t *destenation, const linkedListHead_t *source);
#endif