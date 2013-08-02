#pragma once

struct ir_block;

/**
 * Run (through interpretation) a block and return the result
 */
int runner (const struct ir_block* block);
