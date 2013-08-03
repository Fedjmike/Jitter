#include "jitter.h"

#include "vector.h"

#include "stdarg.h"

/**
 * A chunk of memory containing executable code
 *
 * Used in two distinct phases. Once in the second stage, it may not
 * move back.
 * - Writing the code
 * - Using it as executable memory
 *
 * At the liberty of the implementation this code may be relocated,
 * as such it contains information about which other chunks it references,
 * and which reference it. This will be used to update internal pointers.
 */
typedef struct fchunk {
    void* mem;

    ///Location of pointers within mem that will need relocation
    vector/*<int>*/ relocations;
    ///Other chunks that contain references to this one
    vector/*<fchunk*>*/ references;

    ///Excluding possible relocations, is this chunk complete?
    bool finished;
    ///Is it marked as executable?
    bool executable;
} fchunk;

fchunk* fchunk_create ();
void fchunk_destroy (fchunk* chunk);

/**
 * Attempt to write to the chunk
 * @return success
 */
bool fchunk_vout (fchunk* chunk, const char* format, ...);

/**
 * Mark the chunk as finished. Disallows writing, allows calling.
 */
void fchunk_finish (fchunk* chunk);

/**
 * Attempt to run the code
 * @return success
 */
bool fchunk_call (fchunk* chunk, int* ret);
