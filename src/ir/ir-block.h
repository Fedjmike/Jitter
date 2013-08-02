#pragma once

#include "vector.h"

#include "ir/ir-instr.h"

typedef struct {
    vector/*<ir_instr*>*/ instrs;
    ir_term_instr* terminal;
} ir_block;

ir_block* ir_create_block ();
void ir_destroy_block (ir_block* block);

ir_instr_ref ir_block_add (ir_block* block, ir_instr* instr);
void ir_block_finish (ir_block* block, ir_term_instr* terminal);
