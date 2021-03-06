#include "chayai.h"  // first include!

#include <assert.h>

#include <stdio.h>
#include <brainfuck.h>

BENCHMARK(fabianishere, brainfuck, 100, 1) {
    BrainfuckState *state = brainfuck_state();
    BrainfuckExecutionContext *context = brainfuck_context(BRAINFUCK_TAPE_SIZE);

    BrainfuckInstruction *instruction = brainfuck_parse_string("+[->-[->-[->-[-]<]<]<]>-");
    brainfuck_add(state, instruction);

    brainfuck_execute(state->root, context);
    assert(context->tape_index == 1 && context->tape[0] == 0 && context->tape[1] == 255);

    brainfuck_destroy_context(context);
    brainfuck_destroy_state(state);
}

int main(int argc, char** argv) {

    REGISTER_BENCHMARK(fabianishere, brainfuck); // Brainfuck interpreter written in C

    RUN_BENCHMARKS(argc, argv);

    return 0;
}