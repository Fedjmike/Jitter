#pragma once

#include "instr-ref.h"

typedef enum {
    ir_bop,
    ir_immediate
} ir_instr_tag;

typedef enum {
    ir_bop_undefined,
    ir_bop_add,
    ir_bop_sub,
    ir_bop_mul,
    ir_bop_div
} ir_bop_tag;

/**
 * A value returning, non-terminal IR instruction
 * @see ir_block @see ir_instr_ref
 */
typedef struct ir_instr {
    ir_instr_tag tag;

    union {
        /*bop*/
        struct {
            ir_bop_tag bop;
            ir_instr_ref l, r;
        };
        /*immediate*/
        int imm;
    };
} ir_instr;

const char* ir_instr_tag_get_str (ir_instr_tag tag);
const char* ir_bop_tag_get_str (ir_bop_tag tag);

ir_instr* ir_create_bop (ir_bop_tag bop, ir_instr_ref l, ir_instr_ref r);
ir_instr* ir_create_immediate (int imm);

void ir_destroy_instr (ir_instr* instr);
