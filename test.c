#include "include/linkedList.h"
#include "include/memory.h"

#include <stdlib.h>


int main(void) {
    printf("START\n");
    linkedListHead_t list;
    memory_fill(&list, 0, sizeof(list));

    list.memoryAllocate = calloc;
    list.memoryFree = free;


    linkedList_append(&list, LINKEDLISTTYPES_INT(10));
    linkedList_append(&list, LINKEDLISTTYPES_INT(20));
    linkedList_append(&list, LINKEDLISTTYPES_INT(30));
    test_print_ints(&list);

    printf("Int: %i\n", linkedList_getFirst(&list).int_t);
    printf("Int: %i\n", linkedList_getLast(&list).int_t);
    printf("Int: %i\n", linkedList_get(&list, 1).int_t);

    linkedList_remove(&list, 2);
    test_print_ints(&list);

    printf("LENGTH: %llu\n", list.nodes);

    printf("DONE");

    return 0;
}