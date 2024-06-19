#include "include/linkedList.h"
#include "include/memory.h"

#include <stdlib.h>


int main(void) {
    printf("START\n");
    linkedListHead_t list;
    memory_fill(&list, 0, sizeof(list));

    list.memoryAllocate = calloc;
    list.memoryFree = free;


    for(int i = 0; i < 16; i++) {
        linkedList_append(&list, LINKEDLISTTYPES_INT(i*i));
    }

    test_print_ints(&list);

    printf("LENGTH: %llu\n", list.nodes);

    printf("DONE");

    return 0;
}