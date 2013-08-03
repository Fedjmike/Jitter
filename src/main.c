#include "ir.h"

#include "printer.h"
#include "runner.h"

#include "stdio.h"

int main (int argc, char** argv) {
    (void) argc, (void) argv;

    /* 5*(4+9) */
    ir_block* code = ir_create_block();
    ir_block_finish(code, ir_create_return(
            ir_block_add(code, ir_create_bop(ir_bop_mul,
                               ir_block_add(code, ir_create_immediate(5)),
                               ir_block_add(code, ir_create_bop(ir_bop_add,
                                                  ir_block_add(code, ir_create_immediate(4)),
                                                  ir_block_add(code, ir_create_immediate(9))
                               ))
            ))
    ));

    printer(code);

    /*Run the code and print the result*/
    printf(">> 5*(4+9)\n%d\n", runner(code));

    ir_destroy_block(code);

    return 0;
}
