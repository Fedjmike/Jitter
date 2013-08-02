#pragma once

#include "jitter.h"

typedef struct {
    int length, capacity;
    void** buffer;
} vector;

typedef void (*dtor_type)(void*); ///For use with vector_destroy_objs
typedef void* (*map_type)(void*); ///For use with vector_map

vector vector_create (int initial_capacity);

/**
 * Cleans up resources allocated by the vector but not the vector itself.
 */
void vector_destroy (vector* v);
void vector_destroy_objs (vector* v, void (*dtor)(void*));

void vector_add (vector* v, void* item);

/**
 * Returns the value, or null if out of bounds.
 */
void* vector_get (const vector* v, int n);

/**
 * Attempts to set an index to a value. Returns whether it succeeded
 */
bool vector_set (vector* v, int n, void* value);

/**
 * Maps dest[n] to f(src[n]) for n in src->length.
 *
 * src and dest can match. Lengths not checked.
 * @see mapType
 */
void vector_map (vector* dest, void* (*f)(void*), vector* src);
