#if !defined(RUNTIME_DATA_AREA_H)
#define RUNTIME_DATA_AREA_H

#include "core.h"
#include "class_loader.h"

typedef struct {
    class_file_t *class_data;
    u4_t instruction_pointer;
    u1_t *code;
    u4_t code_length;
    u2_t max_stack;
    u2_t max_locals;
    u2_t stack_count;
    u4_t *locals;
    u4_t *stack;
} frame_t;

typedef struct {
    frame_t *top_frame;
    int stack_size;
} jvm_stack_t;

frame_t * get_frame(int method_count, field_method_info_t * methods ,char * name, int args_count, u4_t * args, cp_info_t * constant_pool);

#endif // RUNTIME_DATA_AREA_H
