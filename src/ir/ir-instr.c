#include "ir/ir-instr.h"

#include "stdlib.h"
#include "string.h"
#include "assert.h"

static ir_instr* ir_create (ir_instr_tag tag);

static ir_instr* ir_create (ir_instr_tag tag) {
    ir_instr* instr = malloc(sizeof(ir_instr));
    /*Zero with memset because of the giant union*/
    memset(instr, 0, sizeof(ir_instr));
    instr->tag = tag;
    return instr;
}

ir_instr* ir_create_bop (ir_bop_tag bop, ir_instr_ref l, ir_instr_ref r) {
    ir_instr* instr = ir_create(ir_bop);
    instr->bop = bop;
    instr->l = l;
    instr->r = r;
    return instr;
}

ir_instr* ir_create_immediate (int imm) {
    ir_instr* instr = ir_create(ir_immediate);
    instr->imm = imm;
    return instr;
}

void ir_destroy_instr (ir_instr* instr) {
    assert(instr != 0);

    free(instr);
}
