#include "vector.h"

#include "stdlib.h"
#include "stdio.h"

vector vector_create (int initial_capacity) {
    vector v;
    v.length = 0;
    v.capacity = initial_capacity;
    v.buffer = malloc(initial_capacity*sizeof(void*));
    return v;
}

void vector_destroy (vector* v) {
    free(v->buffer);
    v->buffer = 0;
}

void vector_destroy_objs (vector* v, dtor_type dtor) {
    /*This will mess up the vector, watevs*/
    vector_map(v, (map_type) dtor, v);
    vector_destroy(v);
}

void vector_add (vector* v, void* item) {
    if (v->length == v->capacity)
        v->buffer = realloc(v->buffer, (v->capacity *= 2)*sizeof(void*));

    v->buffer[v->length++] = item;
}

void* vector_get (const vector* v, int n) {
    if (n < v->length)
        return v->buffer[n];

    else
        return 0;
}

bool vector_set (vector* v, int n, void* value) {
    if (n < v->length) {
        v->buffer[n] = value;
        return false;

    } else
        return true;
}

void vector_map (vector* dest, map_type f, vector* src) {
    for (int n = 0; n < src->length; n++)
        dest->buffer[n] = f(src->buffer[n]);
}
