#include <nlibc/linkedList.h>

#include <stdio.h>

#include <stdint.h>

#include <string.h>

#include <stdlib.h>

int32_t comp(void* data1, void* data2, __attribute__((unused)) const linkedListHead_t* head) {
	if(*((int*)data1) == *((int*)data2)) return 0;
	if(*((int*)data1) < *((int*)data2)) return -1;
	return 1;
}

bool isSorted(linkedListHead_t* head) {
	if(head->nodes == 0) return true;
	if(head->nodes == 1) return true;

	for(int64_t i = 1; i < head->nodes; i++) {
		if(head->data_compare(linkedList_get(head, i - 1), linkedList_get(head, i), head) == 1) return false;
	}
	return true;
}


int main(int argc, char** argv) {

	if(argc < 2) return -1;
	for(size_t i = 0; i < strlen(argv[1]); i++) {
		if(argv[1][i] < '0') return -1;
		if(argv[1][i] > '9') return -1;
	}

	linkedListHead_t head = linkedList_create(sizeof(int), comp);

	printf("Creating List\n");
	int data;
	for(int i = 0; i < atoi(argv[1]); i++) {
		data = rand();
		linkedList_append(&head, &data);
	} 
	printf("Created List\n");

	printf("Lenght: %lu\n", head.nodes);

	printf("SORT\n");
	linkedList_qsort(&head);
	printf("SORT DONE\n");

	if(isSorted(&head)) {
		printf("SORTED\n");
	} else {
		printf("NOT SORTED!\n");
	}

	printf("Deleting List\n");
	linkedList_delete(&head);

	return 0;
}