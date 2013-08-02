#include "ir/ir-term-instr.h"

#include "stdlib.h"
#include "string.h"
#include "assert.h"

static ir_term_instr* ir_create_terminal (ir_term_instr_tag tag);

static ir_term_instr* ir_create_terminal (ir_term_instr_tag tag) {
    ir_term_instr* terminal = malloc(sizeof(ir_term_instr));
    memset(terminal, 0, sizeof(ir_term_instr));
    terminal->tag = tag;
    return terminal;
}

ir_term_instr* ir_create_return (ir_instr_ref ret) {
    ir_term_instr* terminal = ir_create_terminal(ir_return);
    terminal->ret = ret;
    return terminal;
}

void ir_destroy_term_instr (ir_term_instr* terminal) {
    assert(terminal != 0);

    free(terminal);
}
