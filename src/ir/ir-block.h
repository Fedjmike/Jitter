#pragma once

#include "vector.h"

#include "ir/ir-instr.h"

/**
 * A list of instructions possibly followed by a terminator
 * @see ir_instr @see ir_instr_ref @see ir_term_instr
 */
typedef struct {
    vector/*<ir_instr*>*/ instrs;
    ir_term_instr* terminal;
} ir_block;

ir_block* ir_create_block ();
void ir_destroy_block (ir_block* block);

/**
 * Add an instruction as the next to be executed in the block
 *
 * @return a reference to the instruction, to be used as the input
 *         to other instructions
 */
ir_instr_ref ir_block_add (ir_block* block, ir_instr* instr);

/**
 * Provide a terminal instruction for the block
 *
 * @return non-zero on error (usually, block already has terminal)
 */
int ir_block_finish (ir_block* block, ir_term_instr* terminal);
