#include "toy_jvm.h"
#include <stdlib.h>
#include <string.h>

static u1_t read_u1(FILE *fp) {
    return (u1_t)fgetc(fp);
}

static u2_t read_u2(FILE *fp) {
    u1_t b1 = read_u1(fp);
    u1_t b2 = read_u1(fp);
    return (b1 << 8) | b2;
}

static u4_t read_u4(FILE *fp) {
    u2_t b1 = read_u2(fp);
    u2_t b2 = read_u2(fp);
    return (b1 << 16) | b2;
}

static char* read_utf8(FILE *fp, u2_t length) {
    char *str = (char*)malloc(length + 1);
    fread(str, sizeof(char), length, fp);
    str[length] = '\0';
    return str;
}

class_t* load_class(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return NULL;

    class_t *class_data = (class_t*)malloc(sizeof(class_t));
    class_data->magic = read_u4(fp);
    class_data->minor_version = read_u2(fp);
    class_data->major_version = read_u2(fp);
    class_data->constant_pool_count = read_u2(fp);

    class_data->constant_pool = (cp_info_t*)malloc(sizeof(cp_info_t) * class_data->constant_pool_count);
    for (int i = 1; i < class_data->constant_pool_count; i++) {
        cp_info_t *cp_entry = &class_data->constant_pool[i];
        cp_entry->tag = read_u1(fp);
        switch (cp_entry->tag) {
            case CONST_UTF8:
                cp_entry->info.utf8_info.length = read_u2(fp);
                cp_entry->info.utf8_info.bytes = read_utf8(fp, cp_entry->info.utf8_info.length);
                break;
            case CONST_CLASS:
                cp_entry->info.name_index = read_u2(fp);
                break;
            case CONST_STRING:
                cp_entry->info.string_index = read_u2(fp);
                break;
            case CONST_FIELD_REF:
            case CONST_METHOD_REF:
                cp_entry->info.ref_info.class_index = read_u2(fp);
                cp_entry->info.ref_info.name_and_type_index = read_u2(fp);
                break;
            case CONST_NAME_AND_TYPE:
                cp_entry->info.name_and_type_info.name_index = read_u2(fp);
                cp_entry->info.name_and_type_info.descriptor_index = read_u2(fp);
                break;
            default:
                break;
        }
    }

    class_data->access_flags = read_u2(fp);
    class_data->this_class = read_u2(fp);
    class_data->super_class = read_u2(fp);
    class_data->interfaces_count = read_u2(fp);
    class_data->interfaces = (u2_t*)malloc(sizeof(u2_t) * class_data->interfaces_count);
    for (int i = 0; i < class_data->interfaces_count; i++) {
        class_data->interfaces[i] = read_u2(fp);
    }

    class_data->fields_count = read_u2(fp);
    class_data->methods_count = read_u2(fp);
    class_data->methods = (method_info_t*)malloc(sizeof(method_info_t) * class_data->methods_count);
    for (int i = 0; i < class_data->methods_count; i++) {
        method_info_t *method = &class_data->methods[i];
        method->access_flags = read_u2(fp);
        method->name_index = read_u2(fp);
        method->descriptor_index = read_u2(fp);
        method->attributes_count = read_u2(fp);
        for (int j = 0; j < method->attributes_count; j++) {
            u2_t attr_name_index = read_u2(fp);
            u4_t attr_length = read_u4(fp);
            if (strcmp(class_data->constant_pool[attr_name_index].info.utf8_info.bytes, "Code") == 0) {
                method->code_attr.attribute_name_index = attr_name_index;
                method->code_attr.attribute_length = attr_length;
                method->code_attr.max_stack = read_u2(fp);
                method->code_attr.max_locals = read_u2(fp);
                method->code_attr.code_length = read_u4(fp);
                method->code_attr.code = (u1_t*)malloc(method->code_attr.code_length);
                fread(method->code_attr.code, sizeof(u1_t), method->code_attr.code_length, fp);
            } else {
                fseek(fp, attr_length, SEEK_CUR);
            }
        }
    }

    class_data->attributes_count = read_u2(fp);

    fclose(fp);
    return class_data;
}

void exec(frame_t *frame) {
    while (frame->ip < frame->code_attr.code_length) {
        u1_t op = frame->code[frame->ip];
        switch (op) {
            case 0x1a: // iload_0
                frame->stack[frame->stack_top++] = frame->locals[0];
                break;
            case 0x1b: // iload_1
                frame->stack[frame->stack_top++] = frame->locals[1];
                break;
            case 0x60: // iadd
                frame->stack[frame->stack_top - 2] = frame->stack[frame->stack_top - 2] + frame->stack[frame->stack_top - 1];
                frame->stack_top--;
                break;
            case 0xac: // ireturn
                printf("%d\n", frame->stack[--frame->stack_top]);
                return;
            default:
                printf("Unsupported opcode: %02x\n", op);
                return;
        }
        frame->ip++;
    }
}

void free_class(class_t *class_data) {
    for (int i = 1; i < class_data->constant_pool_count; i++) {
        if (class_data->constant_pool[i].tag == CONST_UTF8) {
            free(class_data->constant_pool[i].info.utf8_info.bytes);
        }
    }
    free(class_data->constant_pool);
    for (int i = 0; i < class_data->methods_count; i++) {
        free(class_data->methods[i].code_attr.code);
    }
    free(class_data->methods);
    free(class_data->interfaces);
    free(class_data);
}

int main() {
    class_t *class_data = load_class("Add.class");
    if (!class_data) {
        fprintf(stderr, "Failed to load class file.\n");
        return 1;
    }

    frame_t frame;
    frame.class_data = class_data;
    for (int i = 0; i < class_data->methods_count; i++) {
        method_info_t *method = &class_data->methods[i];
        if (strcmp(class_data->constant_pool[method->name_index].info.utf8_info.bytes, "add") == 0) {
            frame.code = method->code_attr.code;
            frame.code_attr.code_length = method->code_attr.code_length;
            frame.max_stack = method->code_attr.max_stack;
            frame.max_locals = method->code_attr.max_locals;
            frame.locals = (int32_t*)calloc(frame.max_locals, sizeof(int32_t));
            frame.stack = (int32_t*)malloc(frame.max_stack * sizeof(int32_t));
            frame.stack_top = 0;
            frame.ip = 0;

            frame.locals[0] = 2;
            frame.locals[1] = 3;

            exec(&frame);
            free(frame.locals);
            free(frame.stack);
        }
    }

    free_class(class_data);
    return 0;
}
