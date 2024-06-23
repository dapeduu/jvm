#include <string.h>
#include <stdlib.h>
#include "class_loader.h"
#include "runtime_data_area.h"

frame_t * get_frame(int method_count, field_method_info_t * methods ,char * name, int args_count, u4_t * args, cp_info_t * constant_pool) {
    for (size_t i = 0; i < method_count; i++)
    {
        field_method_info_t current_method = methods[i];
        char * method_name = get_constant_pool_value(constant_pool, current_method.name_index);
        if (strcmp(method_name, name)) continue;

        for (size_t j = 0; j < current_method.attributes_count; j++)
        {
            attribute_info_t current_attribute = current_method.attributes[j];
            char * attribute_name = get_constant_pool_value(constant_pool, current_attribute.attribute_name_index);
            if (strcmp(attribute_name, "Code")) continue;
            frame_t * current_frame = malloc(sizeof(frame_t));

            current_frame->max_stack = (current_attribute.bytes[0] << 8) | current_attribute.bytes[1];

            current_frame->max_locals = (current_attribute.bytes[2] << 8) | current_attribute.bytes[3];

            current_frame->code_length = (current_attribute.bytes[4] << 24) | (current_attribute.bytes[5] << 16) | (current_attribute.bytes[6] << 8) | current_attribute.bytes[7];

            current_frame->code = malloc(sizeof(u1_t) * current_frame->code_length);

            memcpy(current_frame->code, current_attribute.bytes + 8, current_frame->code_length);

            current_frame->locals = calloc(current_frame->max_locals, sizeof(u1_t));

            for (size_t k = 0; k < args_count; k++)
            {
                current_frame->locals[k] = args[k];
            }

            current_frame->stack = malloc(current_frame->max_stack * sizeof(u4_t));
            current_frame->stack_count = 0;

            return current_frame;
        }
    }

    printf("Erro: não encontrou um frame");
    exit(1);
}