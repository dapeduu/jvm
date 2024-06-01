#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "consts.h"

class_file_t *read_class_file(FILE *fptr)
{
    class_file_t *class_file = malloc(sizeof(class_file_t));

    class_file->magic = read_u4(fptr);
    class_file->minor_version = read_u2(fptr);
    class_file->major_version = read_u2(fptr);
    class_file->constant_pool_count = read_u2(fptr);
    class_file->constant_pool = malloc(sizeof(cp_info_t) * class_file->constant_pool_count);

    cp_info_t current_constant_pool;
    for (size_t i = 0; i < class_file->constant_pool_count - 1; i++)
    {
        current_constant_pool.tag = read_u1(fptr);
        switch (current_constant_pool.tag)
        {
        case CONSTANT_Class:
            current_constant_pool.info.class.name_index = read_u2(fptr);
            break;
        case CONSTANT_Fieldref:
            current_constant_pool.info.fieldref.class_index = read_u2(fptr);
            current_constant_pool.info.fieldref.name_and_type_index = read_u2(fptr);
            break;
        case CONSTANT_Methodref:
            current_constant_pool.info.methodref.class_index = read_u2(fptr);
            current_constant_pool.info.methodref.name_and_type_index = read_u2(fptr);
            break;
        case CONSTANT_InterfaceMethodref:
            current_constant_pool.info.interface_methodref.class_index = read_u2(fptr);
            current_constant_pool.info.interface_methodref.name_and_type_index = read_u2(fptr);
            break;
        case CONSTANT_String:
            current_constant_pool.info.string.string_index = read_u2(fptr);
            break;
        case CONSTANT_Integer:
            current_constant_pool.info.integer.bytes = read_u4(fptr);
            break;
        case CONSTANT_Float:
            current_constant_pool.info.float_num.bytes = read_u4(fptr);
            break;
        case CONSTANT_Long:
            current_constant_pool.info.long_num.high_bytes = read_u4(fptr);
            current_constant_pool.info.long_num.low_bytes = read_u4(fptr);
            break;
        case CONSTANT_Double:
            current_constant_pool.info.double_num.high_bytes = read_u4(fptr);
            current_constant_pool.info.double_num.low_bytes = read_u4(fptr);
            break;
        case CONSTANT_NameAndType:
            current_constant_pool.info.name_and_type.name_index = read_u2(fptr);
            current_constant_pool.info.name_and_type.descriptor_index = read_u2(fptr);
            break;
        case CONSTANT_Utf8:
            current_constant_pool.info.utf8.length_of_byte_array = read_u2(fptr);
            current_constant_pool.info.utf8.string = malloc(
                current_constant_pool.info.utf8.length_of_byte_array);

            fread(current_constant_pool.info.utf8.string,
                  1,
                  current_constant_pool.info.utf8.length_of_byte_array,
                  fptr);
            break;
        default:
            printf("Unhandled constant pool tag: %i\n", current_constant_pool.tag);
            printf("Current constant pool count: %i\n", class_file->constant_pool_count - 1);
            printf("Current constant pool entry: %li\n", i);
            exit(1);
            break;
        }

        class_file->constant_pool[i] = current_constant_pool;
    }

    class_file->access_flags = read_u2(fptr);
    class_file->this_class = read_u2(fptr);
    class_file->super_class = read_u2(fptr);
    class_file->interfaces_count = read_u2(fptr);
    // class_file->interfaces = malloc(sizeof(u2_t) * class_file->interfaces_count);



    return class_file;
}

int free_class_file(class_file_t *class_file)
{

    // Free all utf8 strings from constant pool
    for (size_t i = 0; i < class_file->constant_pool_count; i++)
    {
        if (class_file->constant_pool[i].tag != CONSTANT_Utf8)
            continue;

        free(class_file->constant_pool[i].info.utf8.string);
    }
    free(class_file->constant_pool);
    free(class_file);

    return 0;
}