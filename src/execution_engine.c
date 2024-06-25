#include <stdlib.h>
#include <math.h>
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
        case 112: // irem
            irem(frame);
            break;
        case 113: // lrem
            lrem(frame);
            break;
        case 114: // frem
            frem(frame);
            break;
        case 115: // drem
            // TODO: drem
            break;
        case 126: // iand
            iand(frame);
            break;
        case 127: // land
            land(frame);
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

float make_float(uint32_t number) {
    return *(float *)&number;
}

long make_long(uint32_t high, uint32_t low) {
    uint64_t number;
    number = (((uint64_t)high) << 32) | ((uint64_t)low);
    return *(long *)&number;
}

double make_double(uint32_t high, uint32_t low) {
    uint64_t number;

    number = (((uint64_t)high) << 32) | ((uint64_t)low);

    return *(double *)&number;
}

uint32_t float_to_uint32(float number) {
    return *(uint32_t *)&number;
}

uint64_t double_to_uint64(double number) {
    return *(uint64_t *)&number;
}

void iand(frame_t * frame) {
    u4_t value1 = pop(frame);
    u4_t value2 = pop(frame);
    u4_t res = value1 &= value2;
    push(frame, res);
};

void land(frame_t * frame) {
    u4_t value1_hi = pop(frame);
    u4_t value1_lo = pop(frame);
    u4_t value2_hi = pop(frame);
    u4_t value2_lo = pop(frame);

    long value1 = make_long(value1_hi, value1_lo);
    long value2 = make_long(value2_hi, value2_lo);
    long res = value1 &= value2;

    u4_t res_hi = (u4_t) (res >> 32) & 0x00000000FFFFFFFF;
    u4_t res_lo = (u4_t) res & 0x00000000FFFFFFFF;

    push(frame, res_hi);
    push(frame, res_lo);
};

void irem(frame_t * frame) {
    u4_t value1 = pop(frame);
    u4_t value2 = pop(frame);
    u4_t res = value1 % value2;
    // if value2 == 0 ArithmeticException
    push(frame, res);
}

void lrem(frame_t * frame) {
    u4_t value1_hi = pop(frame);
    u4_t value1_lo = pop(frame);
    u4_t value2_hi = pop(frame);
    u4_t value2_lo = pop(frame);

    long value1 = make_long(value1_hi, value1_lo);
    long value2 = make_long(value2_hi, value2_lo);
    // if value2 == 0 ArithmeticException

    u8_t res = value1 % value2;
    u4_t res_hi = (u4_t) (res >> 32) & 0x00000000FFFFFFFF;
    u4_t res_lo = (u4_t) res & 0x00000000FFFFFFFF;

    push(frame, res_hi);
    push(frame, res_lo);
}

void frem(frame_t * frame) {
    u4_t value1 = pop(frame);
    u4_t value2 = pop(frame);

    float res = fmod(make_float(value1), make_float(value2));

    push(frame, float_to_uint32(res));
}

// drem teria conflito de nome com função em math.h
void drem_handler(frame_t *frame) {
    u4_t value1_hi = pop(frame);
    u4_t value1_lo = pop(frame);
    u4_t value2_hi = pop(frame);
    u4_t value2_lo = pop(frame);

    u8_t value1 = make_double(value1_hi, value1_lo);
    u8_t value2 = make_double(value2_hi, value2_lo);

    u8_t res = double_to_uint64(fmod(value1, value2));
    u4_t res_hi = (u4_t) (res >> 32) & 0x00000000FFFFFFFF;
    u4_t res_lo = (u4_t) res & 0x00000000FFFFFFFF;

    push(frame, res_hi);
    push(frame, res_lo);
}


