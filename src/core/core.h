#include <stdint.h>
#include <stdio.h>

// Base types
typedef uint8_t u1_t;
typedef uint16_t u2_t;
typedef uint32_t u4_t;
// typedef unsigned long u8_t; N será possível ler u8 com 32bits

typedef struct
{
    u1_t tag;
    union
    {
        // Tag: 7
        struct
        {
            u2_t name_index;
        } class;

        // Tag: 9
        struct
        {
            u2_t class_index;
            u2_t name_and_type_index;
        } fieldref;

        // Tag: 10
        struct
        {
            u2_t class_index;
            u2_t name_and_type_index;
        } methodref;

        // tag: 11
        struct
        {
            u2_t class_index;
            u2_t name_and_type_index;
        } interface_methodref;

        // Tag: 8
        struct
        {
            u2_t string_index;
        } string;

        // Tag: 3
        struct
        {
            u4_t bytes;
        } integer;

        // Tag: 4
        struct
        {
            u4_t bytes;
        } float_num;

        // Tag: 5
        struct
        {
            u4_t high_bytes;
            u4_t low_bytes;
        } long_num;

        // Tag: 6
        struct
        {
            u4_t high_bytes;
            u4_t low_bytes;
        } double_num;

        // Tag 12
        struct
        {
            u2_t name_index;
            u2_t descriptor_index;
        } name_and_type;

        // Tag: 1
        struct
        {
            u2_t length_of_byte_array;
            u1_t *string;
        } utf8;

    } info;
} cp_info_t;

typedef struct
{
    u2_t access_flags;
    u2_t name_index;
    u2_t descriptor_index;
    u2_t attributes_count;
    // attribute_info attributes [attributes_count];
} field_info; 

typedef struct
{
    u4_t magic;
    u2_t minor_version;
    u2_t major_version;
    u2_t constant_pool_count;
    cp_info_t *constant_pool;
    u2_t access_flags;
    u2_t this_class;
    u2_t super_class;
    u2_t interfaces_count;
    u2_t * interfaces;
    u2_t fields_count;
    field_info *fields;
    // TODO: Terminar essas
    // u2 methods_count;
    // method_info methods [methods_count];
    // u2 attributes_count;
    // attribute_info attributes [attributes_count];
} class_file_t;

// readers.c
u4_t read_u4(FILE *fptr);
u2_t read_u2(FILE *fptr);
u1_t read_u1(FILE *fptr);

// classfile.c
class_file_t *read_class_file(FILE *fptr);
int free_class_file(class_file_t *class_file);