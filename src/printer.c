#include "printer.h"

#include "debug.h"

#include "ir.h"

#include "stdio.h"

static void print_block (const ir_block* block);
static void print_instr (const ir_instr* instr);
static void print_terminal (const ir_term_instr* terminal);

void printer (const ir_block* block) {
    print_block(block);
}

static void print_block (const ir_block* block) {
    printf("block:\n");

    for (int i = 0; i < block->instrs.length; i++) {
        printf("  %%%03d = ", i);
        print_instr(vector_get(&block->instrs, i));
    }

    if (block->terminal) {
        printf("  ");
        print_terminal(block->terminal);
    }

    printf("\n");
}

static void print_instr (const ir_instr* instr) {
    switch (instr->tag) {
        case ir_bop:
            printf("%s %%%03d %%%03d\n", ir_bop_tag_get_str(instr->bop), instr->l, instr->r);

        break;
        case ir_immediate:
            printf("imm %d\n", instr->imm);

        break;
        default:
            debug_error_unhandled("print_instr", "instruction tag", ir_instr_tag_get_str(instr->tag));
            printf("<unhandled>\n");
    }
}

static void print_terminal (const ir_term_instr* terminal) {
    switch (terminal->tag) {
        case ir_return:
            printf("return %%%03d\n", terminal->ret);

        break;
        default:
            debug_error_unhandled("print_terminal", "instruction tag", ir_term_instr_tag_get_str(terminal->tag));
            printf("<unhandled>\n");
    }
}
