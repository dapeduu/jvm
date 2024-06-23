#ifndef TOY_JVM_H
#define TOY_JVM_H

#include <stdint.h>
#include <stdio.h>

typedef uint8_t u1_t;
typedef uint16_t u2_t;
typedef uint32_t u4_t;
typedef uint64_t u8_t;

typedef enum {
    CONST_UTF8 = 1,
    CONST_CLASS = 7,
    CONST_STRING = 8,
    CONST_FIELD_REF = 9,
    CONST_METHOD_REF = 10,
    CONST_NAME_AND_TYPE = 12
} ConstTag;

typedef struct {
    u1_t tag;
    union {
        struct {
            u2_t length;
            char *bytes;
        } utf8_info;
        u2_t name_index;
        u2_t class_index;
        u2_t string_index;
        struct {
            u2_t class_index;
            u2_t name_and_type_index;
        } ref_info;
        struct {
            u2_t name_index;
            u2_t descriptor_index;
        } name_and_type_info;
    } info;
} cp_info_t;

typedef struct {
    u2_t access_flags;
    u2_t name_index;
    u2_t descriptor_index;
    u2_t attributes_count;
    // Attributes (simplified, only Code attribute considered)
    struct {
        u2_t attribute_name_index;
        u4_t attribute_length;
        u2_t max_stack;
        u2_t max_locals;
        u4_t code_length;
        u1_t *code;
    } code_attr;
} method_info_t;

typedef struct {
    u4_t magic;
    u2_t minor_version;
    u2_t major_version;
    u2_t constant_pool_count;
    cp_info_t *constant_pool;
    u2_t access_flags;
    u2_t this_class;
    u2_t super_class;
    u2_t interfaces_count;
    u2_t *interfaces;
    u2_t fields_count;
    u2_t methods_count;
    method_info_t *methods;
    u2_t attributes_count;
} class_t;

typedef struct {
    class_t *class_data;
    u4_t ip;
    u1_t *code;
    u2_t max_stack;
    u2_t max_locals;
    int32_t *locals;
    int32_t *stack;
    int32_t stack_top;
} frame_t;

class_t* load_class(const char *filename);
void exec(frame_t *frame);
void free_class(class_t *class_data);

#endif // TOY_JVM_H
