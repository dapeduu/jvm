#include <stdlib.h>
#include "core.h"
#include "runtime_data_area.h"
#include "execution_engine.h"

static void push(frame_t * frame, u4_t argument) {
    frame->stack[frame->stack_count] = argument;
    frame->stack_count += 1;
}

static u4_t pop(frame_t * frame) {
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
        
        switch (opcode)
        {
        case 26: // iload_0
            push(frame, frame->locals[0]);
            break;
        
        case 27: // iload_1
            push(frame, frame->locals[1]);
            break;
        case 96: // add
            u4_t value1 = pop(frame);
            u4_t value2 = pop(frame);
            push(frame, value1 + value2);
            break;
        case 172: // ireturn
            return pop(frame);
        default:
            break;
        }

        frame->instruction_pointer++;
    }

    printf("Erro: Não entrou no return");
    exit(1);
}