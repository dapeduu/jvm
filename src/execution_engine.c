/**
 * @file execution_engine.c
 * @brief Implementação das funções de execução.
 * Declara e usa funções da pilha de frames.
 * Roda o frame chamando uma instrução por vez.
 */

#include <stdlib.h>
#include "core.h"
#include "handlers.h"
#include "runtime_data_area.h"
#include "execution_engine.h"

/**
 * @brief Função push.
 *
 * Coloca um argumento na pilha.
 *
 * @param[in]  frame  Ponteiro para o frame.
 * @param[in] argument  Argumento a ser colocado na pilha.
 * @return void.
 */

void push(frame_t * frame, u4_t argument) {
    frame->stack[frame->stack_count] = argument;
    frame->stack_count += 1;
}

/**
 * @brief Função pop.
 *
 * Retira o último argumento da pilha.
 *
 * @param[in]  frame  Ponteiro para o frame.
 * @return Último argumento da pilha.
 */

u4_t pop(frame_t * frame) {
    frame->stack_count -= 1;
    return frame->stack[frame->stack_count];
}

/**
 * @brief Função run_frame.
 * 
 * Roda o frame, chamando uma instrução por vez.
 * @param frame 
 * @return u4_t 
 */
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
            printf("Instrução não encontrada. Opcode: %x\n", opcode);
            exit(1);
        }

        frame->instruction_pointer++;
    }
    return 0;

}

