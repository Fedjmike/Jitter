#include "runner.h"

#include "debug.h"

#include "ir/ir-instr.h"
#include "ir/ir-term-instr.h"
#include "ir/ir-block.h"

#include "stdlib.h"

static int run_block (const ir_block* block);
static int run_instr (const ir_instr* instr, const int* store);
static int run_terminal (const ir_term_instr* terminal, const int* store);

int runner (const ir_block* block) {
    return run_block(block);
}

static int run_block (const ir_block* block) {
    int* store = calloc(block->instrs.length, sizeof(int));

    /*Execute each instruction, storing its value*/
    for (int i = 0; i < block->instrs.length; i++)
        store[i] = run_instr(vector_get(&block->instrs, i), store);

    int result = 0;

    if (block->terminal)
        return run_terminal(block->terminal, store);

    free(store);

    return result;
}

static int run_instr (const ir_instr* instr, const int* store) {
    switch (instr->tag) {
        case ir_bop:
            /*Labels must label statements, silly standard*/;
            int l = store[instr->l], r = store[instr->r];

            switch (instr->bop) {
                case ir_bop_add: return l+r;
                case ir_bop_sub: return l-r;
                case ir_bop_mul: return l*r;
                case ir_bop_div: return l/r;

                case ir_bop_undefined:
                    debug_msg("Unhandled in run_instr");
                    return 0;

                default:
                    debug_error_unhandled("run_instr", "operation", ir_bop_tag_get_str(instr->bop));
                    return 0;
            }

        break;
        case ir_immediate: return instr->imm;

        default:
            debug_error_unhandled("run_instr", "instruction tag", ir_instr_tag_get_str(instr->tag));
            return 0;
    }
}

static int run_terminal (const ir_term_instr* terminal, const int* store) {
    switch (terminal->tag) {
        case ir_return: return store[terminal->ret];

        default:
            debug_error_unhandled("run_terminal", "instruction tag", ir_term_instr_tag_get_str(terminal->tag));
            return 0;
    }
}
