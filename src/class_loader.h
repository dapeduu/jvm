#if !defined(CLASS_LOADER_H)
#define CLASS_LOADER_H

#include <stdio.h>
#include "core.h"

// Class definitions
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

typedef struct {
    u2_t attribute_name_index;
    u4_t attribute_length;
    u1_t *bytes;
} attribute_info_t;

typedef struct
{
    u2_t access_flags;
    u2_t name_index;
    u2_t descriptor_index; 
    u2_t attributes_count;
    attribute_info_t *attributes;
} field_method_info_t;

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
    field_method_info_t *fields;
    u2_t attributes_count;
    attribute_info_t *attributes;
    u2_t methods_count;
    field_method_info_t *methods;
} class_file_t;

// Reader functions
u4_t read_u4(FILE *fptr);
u2_t read_u2(FILE *fptr);
u1_t read_u1(FILE *fptr);
char* get_constant_pool_value(cp_info_t * cp_info, u2_t name_index);
class_file_t *read_class_file(FILE *fptr);

#endif // CLASS_LOADER_H