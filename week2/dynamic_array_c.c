#include <stdlib.h>
#include <stdio.h>

typedef struct dynamic_int_array {
	int* ptr;
	int length;
	int capacity;
} dynamic_int_array_t;

void dynamic_int_array_allocate(dynamic_int_array_t* arr) {
	arr->ptr = (int*)malloc(sizeof(int) * 10);
	arr->length = 0;
	arr->capacity = 10;
}

void dynamic_int_array_deallocate(dynamic_int_array_t* arr) {
	free(arr->ptr);
}

void dynamic_int_array_append_data(dynamic_int_array_t* arr, int data) {
	if(arr->length == arr->capacity) {
		int* new_ptr = (int*)malloc(sizeof(int) * 2 * arr->capacity);
		for(int i = 0; i < arr->capacity; i++) {
			new_ptr[i] = arr->ptr[i];
		}
		arr->capacity *= 2;
		free(arr->ptr);
		arr->ptr = new_ptr;
	}
	arr->ptr[arr->length] = data;
	++arr->length;
}

int dynamic_int_array_length(dynamic_int_array_t* arr) {
	return arr->length;
}
int dynamic_int_array_at(dynamic_int_array_t* arr, int idx) {
	return arr->ptr[idx];
}

int main() {
	dynamic_int_array_t arr;
	dynamic_int_array_allocate(&arr);

	for(int i = 0; i < 100; i++) {
		dynamic_int_array_append_data(&arr, i);
	}

	for(int i = 0; i < dynamic_int_array_length(&arr); i++) {
		printf("%d ", dynamic_int_array_at(&arr, i));
	}
	printf("\n");

	dynamic_int_array_deallocate(&arr);
	return 0;
}
