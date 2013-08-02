#include "ir/ir-block.h"

#include "stdlib.h"
#include "assert.h"

ir_block* ir_create_block () {
    ir_block* block = malloc(sizeof(ir_block));
    block->instrs = vector_create(32);
    block->terminal = 0;
    return block;
}

void ir_destroy_block (ir_block* block) {
    assert(block != 0);

    vector_destroy_objs(&block->instrs, (dtor_type) ir_destroy_instr);
    ir_destroy_term_instr(block->terminal);

    free(block);
}

ir_instr_ref ir_block_add (ir_block* block, const ir_instr* instr) {
    int index = block->instrs.length;
    vector_add(&block->instrs, (void*) instr);
    return index;
}

bool ir_block_finish (ir_block* block, ir_term_instr* terminal) {
    if (!block->terminal) {
        block->terminal = terminal;
        return true;

    } else {
        ir_destroy_term_instr(terminal);
        return false;
    }
}
