#include "term-instr.h"

#include "debug.h"

#include "stdlib.h"
#include "string.h"
#include "assert.h"

static ir_term_instr* ir_create_terminal (ir_term_instr_tag tag);

/*:::: Terminal Tags ::::*/

const char* ir_term_instr_tag_get_str (ir_term_instr_tag tag) {
    switch (tag) {
        case ir_return: return "ir_return";
        default:
            debug_error_unhandled_int("ir_term_instr_tag_get_str", "instruction tag", tag);
            return "<unhandled>";
    }
}

/*:::: Terminal Instructons ::::*/

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
