#ifndef NLIBC_LINKED_LIST_H
#define NLIBC_LINKED_LIST_H

#include "stdtypes.h"

union linkedListTypes;

#define LINKEDLISTTYPES_CHAR(x) ((union linkedListTypes){.char_t = x})
#define LINKEDLISTTYPES_SHORT(x) ((union linkedListTypes){.short_t = x})
#define LINKEDLISTTYPES_INT(x) ((union linkedListTypes){.int_t = x})
#define LINKEDLISTTYPES_LONG(x) ((union linkedListTypes){.long_t_t = x})
#define LINKEDLISTTYPES_FLOAT(x) ((union linkedListTypes){.float_t = x})
#define LINKEDLISTTYPES_BOOL(x) ((union linkedListTypes){.bool_t = x})
#define LINKEDLISTTYPES_DOUBLE(x) ((union linkedListTypes){.double_t = x})
#define LINKEDLISTTYPES_LONGLONG(x) ((union linkedListTypes){.longlong_t = x})
#define LINKEDLISTTYPES_PTR(x) ((union linkedListTypes){.ptr_t = x})

union linkedListTypes {
    char char_t;
    short short_t;
    int int_t;
    long long_t;
    float float_t;
    _Bool bool_t;
    double double_t;
    long long longlong_t;
    void* ptr_t;
};

struct linkedList_node;

typedef struct linkedList_head {
    union {
        struct linkedList_node *firstNode;  //the firstNode and begin of the list are the same
        struct linkedList_node *list;
    };
    struct linkedList_node *lastNode;
    uint64_t nodes;

    uint32_t (*data_compare)(union linkedListTypes, union linkedListTypes); // returns -1 if first "object" is smaller than the second, 0 is theyre eqal and 1 if the second is larger
    void (*data_delete)(union linkedListTypes);
    bool (*data_validate)(union linkedListTypes);
    void (*data_rectify)(union linkedListTypes);
    union linkedListTypes (*data_copy)(union linkedListTypes);
    void* (*memoryAllocate)(uint64_t, uint64_t);
    void (*memoryFree)(void*);
    void (*memoryFreeData)(union linkedListTypes);

} linkedListHead_t;

typedef struct linkedList_node {
    union linkedListTypes data;

    struct linkedList_node *nextNode;
    struct linkedList_node *prevNode;
    struct linkedList_head *listHead;
} linkedListNode_t;

//void linkedList_create(linkedListHead_t *head);
void linkedList_delete(linkedListHead_t *head);

bool linkedList_validate(const linkedListHead_t *head);
void linkedList_rectify(linkedListHead_t *head);

void linkedList_append(linkedListHead_t *head, union linkedListTypes data);
void linkedList_prepend(linkedListHead_t *head, union linkedListTypes data);
void linkedList_insert(linkedListHead_t *head, uint64_t index, union linkedListTypes data);

void linkedList_removeLast(linkedListHead_t *head);
void linkedList_removeFirst(linkedListHead_t *head);
void linkedList_remove(linkedListHead_t *head, uint64_t index);

union linkedListTypes linkedList_get(linkedListHead_t *head, uint64_t index);

union linkedListTypes linkedList_getFirst(linkedListHead_t *head);

union linkedListTypes linkedList_getLast(linkedListHead_t *head);

void linkedList_set(const linkedListHead_t *head, uint64_t index, union linkedListTypes data);
void linkedList_setFirst(const linkedListHead_t *head, union linkedListTypes data);
void linkedList_setLast(const linkedListHead_t *head, union linkedListTypes data);

//void linkedList_sort(const linkedListHead_t *head);

//int64_t linkedList_find(const linkedListHead_t *head, union linkedListTypes data);

//bool linkedList_contains(const linkedListHead_t *head, union linkedListTypes data);

//void linkedList_copy(linkedListHead_t *destenation, const linkedListHead_t *source);

void linkedList_reverse(linkedListHead_t *head);

//void linkedList_combine(linkedListHead_t *destenation, const linkedListHead_t *source);

void test_print_ints(linkedListHead_t *head);


#endif