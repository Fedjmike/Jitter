#pragma once

#include "jitter.h"
#include "vector.h"

#include "ir/ir-instr.h"
#include "ir/ir-term-instr.h"

/**
 * A list of instructions possibly followed by a terminator
 * @see ir_instr @see ir_instr_ref @see ir_term_instr
 *
 * Has ownership (responsibility to destroy) the instructions (inc. term)
 * in it.
 */
typedef struct {
    vector/*<const ir_instr*>*/ instrs;
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
ir_instr_ref ir_block_add (ir_block* block, const ir_instr* instr);

/**
 * Provide a terminal instruction for the block
 *
 * As the block assumes ownership of the terminal, and this can fail,
 * if it does then it will immediately destroy the terminal.
 *
 * @return Whether it succeeded (block may already have terminal)
 */
bool ir_block_finish (ir_block* block, ir_term_instr* terminal);
