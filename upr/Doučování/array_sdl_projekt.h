#pragma once

// Dynamické pole - každý prvek je ukazatel do haldy
typedef struct {
    void **data;
    int capacity;
    int count;
} Array;

void array_init(Array *array, int capacity) {
    array->data = malloc(sizeof(void *) * capacity);
    array->capacity = capacity;
    array->count = 0;
}
// value has to come from malloc
void array_push(Array *array, void *value) {
    if (array->count == array->capacity) {
        array->capacity = array->capacity * 2;
        array->data = realloc(array->data, sizeof(void *) * array->capacity);
    }

    // char *address = array->data + (array->count * array->element_size);
    // memcpy(address, value, array->element_size);
    array->data[array->count] = value;
    array->count += 1;
}
void array_free(Array *array) {
    for (int i = 0; i < array->count; i++) {
        free(array->data[i]);
    }
    free(array->data);
}

/*
// Dynamické pole - každý prvek má fixní velikost a je uloženo přímo uvnitř pole
typedef struct {
    char *data;
    int element_size;
    int capacity;
    int count;
} Array;

void array_init(Array *array, int capacity, int element_size) {
    array->data = malloc(element_size * capacity);
    array->capacity = capacity;
    array->count = 0;
}
// value has to come from malloc
void array_push(Array *array, void *value) {
    if (array->count == array->capacity) {
        array->capacity = array->capacity * 2;
        array->data = realloc(array->data, array->element_size * array->capacity);
    }

    char *address = array->data + (array->count * array->element_size);
    memcpy(address, value, array->element_size);
}
void array_read(Array *array, int index, void *value) {
    char *address = array->data + (array->count * array->element_size);
    memcpy(value, address, array->element_size);
}
void array_free(Array *array) {
    free(array->data);
}
*/
