#pragma once

#include "ir/ir-instr-ref.h"

typedef enum {
    ir_return
} ir_term_instr_tag;

typedef struct {
    ir_term_instr_tag tag;

    union {
        /*return*/
        ir_instr_ref ret;
    };
} ir_term_instr;

ir_term_instr* ir_create_return (ir_instr_ref ret);

void ir_destroy_term_instr (ir_term_instr* terminal);
