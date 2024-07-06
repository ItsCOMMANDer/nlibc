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
    //linkedList_append(&list, LINKEDLISTTYPES_INT(20));

    test_print_ints(&list);

    linkedList_reverse(&list);

    test_print_ints(&list);

    printf("LENGTH: %llu\n", list.nodes);

    printf("DONE");

    return 0;
}