#pragma once

struct ir_instr;

/**
 * A reference to an instruction
 * @see ir_instr @see ir_block
 *
 * Used as the input to other instructions
 */
typedef struct ir_instr* ir_instr_ref;
