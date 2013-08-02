#pragma once

struct ir_instr;

/**
 * A reference to an instruction
 * @see ir_instr @see ir_block
 *
 * Used as the input to other instructions
 * Valid only within the same block as the instruction it is referencing
 */
typedef int ir_instr_ref;
