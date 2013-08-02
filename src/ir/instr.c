#include "instr.h"

#include "debug.h"

#include "stdlib.h"
#include "string.h"
#include "assert.h"

/*:::: Instruction Tags ::::*/

const char* ir_instr_tag_get_str (ir_instr_tag tag) {
    switch (tag) {
        case ir_bop: return "ir_bop";
        case ir_immediate: return "ir_immediate";
        default:
            debug_error_unhandled_int("ir_instr_tag_get_str", "instruction tag", tag);
            return "<unhandled>";
    }
}

/*:::: BOP Tags ::::*/

const char* ir_bop_tag_get_str (ir_bop_tag tag) {
    switch (tag) {
        case ir_bop_undefined: return "ir_bop_undefined";
        case ir_bop_add: return "ir_bop_add";
        case ir_bop_sub: return "ir_bop_sub";
        case ir_bop_mul: return "ir_bop_mul";
        case ir_bop_div: return "ir_bop_div";
        default:
            debug_error_unhandled_int("ir_bop_tag_get_str", "operation tag", tag);
            return "<unhandled>";
    }
}

/*:::: Instructions ::::*/

static ir_instr* ir_create_instr (ir_instr_tag tag);

static ir_instr* ir_create_instr (ir_instr_tag tag) {
    ir_instr* instr = malloc(sizeof(ir_instr));
    /*Zero with memset because of the giant union*/
    memset(instr, 0, sizeof(ir_instr));
    instr->tag = tag;
    return instr;
}

ir_instr* ir_create_bop (ir_bop_tag bop, ir_instr_ref l, ir_instr_ref r) {
    ir_instr* instr = ir_create_instr(ir_bop);
    instr->bop = bop;
    instr->l = l;
    instr->r = r;
    return instr;
}

ir_instr* ir_create_immediate (int imm) {
    ir_instr* instr = ir_create_instr(ir_immediate);
    instr->imm = imm;
    return instr;
}

void ir_destroy_instr (ir_instr* instr) {
    assert(instr != 0);

    free(instr);
}
