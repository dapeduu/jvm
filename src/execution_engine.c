#include <stdlib.h>
#include "core.h"
#include "handlers.h"
#include "runtime_data_area.h"
#include "execution_engine.h"

void push(frame_t * frame, u4_t argument) {
    frame->stack[frame->stack_count] = argument;
    frame->stack_count += 1;
}

u4_t pop(frame_t * frame) {
    frame->stack_count -= 1;
    return frame->stack[frame->stack_count];
}

u4_t run_frame(frame_t * frame) {
    for (size_t i = 0; i < frame->code_length; i++)
    {
        u4_t opcode = frame->code[frame->instruction_pointer];
        printf("opcode: %02x, stack: ", opcode);
        for (size_t j = 0; j < frame->stack_count; j++)
        {
            printf("%i ", frame->stack[j]);
        }
        printf("\n");

        if (opcode == 172) {
            return pop(frame);
        }

        if (inst_vector[opcode]) {
            inst_vector[opcode](frame);
        } else {
            printf("Instrução não encontrada. Opcode:%i", opcode);
            printf("");
            exit(1);
        }

        frame->instruction_pointer++;
    }
    return 0;

}

