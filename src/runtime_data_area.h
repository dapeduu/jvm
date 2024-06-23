#if !defined(RUNTIME_DATA_AREA)
#define RUNTIME_DATA_AREA

#include "core.h"
#include "class_loader.h"

typedef struct {
    class_file_t *class_data;
    u4_t instruction_pointer;
    u1_t *code;
    u4_t code_length;
    u2_t max_stack;
    u2_t max_locals;
    int32_t *locals;
    int32_t *stack;
} frame_t;

#endif // RUNTIME_DATA_AREA
