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
    test_print_ints(&list);
    linkedList_append(&list, LINKEDLISTTYPES_INT(20));
    test_print_ints(&list);
    linkedList_prepend(&list, LINKEDLISTTYPES_INT(30));
    test_print_ints(&list);
    linkedList_insert(&list, 1, LINKEDLISTTYPES_INT(42));


    test_print_ints(&list);

    printf("LENGTH: %llu\n", list.nodes);

    printf("DONE");

    return 0;
}