#include <stdlib.h>
#include "core.h"
#include "class_loader.h"

u1_t read_u1(FILE *fptr)
{
    u1_t value;

    value = getc(fptr);

    return value;
}

u2_t read_u2(FILE *fptr)
{
    u2_t value;
    u1_t buffer[2];

    fread(buffer, sizeof(u1_t), 2, fptr);

    value = (buffer[0] << 8) | buffer[1];

    return value;
}

u4_t read_u4(FILE *fptr)
{
    u4_t value;
    u1_t buffer[4];

    fread(buffer, sizeof(u1_t), 4, fptr);

    value = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];

    return value;
}

static char* get_constant_pool_value(cp_info_t * cp_info, u2_t name_index) {
    if (cp_info->tag == CONSTANT_String) {
        return (char *)cp_info[name_index-1].info.utf8.string;
    }

    return "";
}

static attribute_info_t *get_attributes(int attributes_count, FILE *fptr)
{
    attribute_info_t *attributes = calloc(attributes_count, sizeof(attribute_info_t));
    for (size_t j = 0; j < attributes_count; j++)
    {
        attributes[j].attribute_name_index = read_u2(fptr);
        attributes[j].attribute_length = read_u4(fptr);
        attributes[j].bytes = malloc(sizeof(u1_t) * attributes[j].attribute_length);

        for (size_t k = 0; k < attributes[j].attribute_length; k++)
        {
            attributes[j].bytes[k] = read_u1(fptr);
        }
    }
    return attributes;
}

static field_method_info_t *get_field_method_info(int fields_count, FILE *fptr)
{
    field_method_info_t *fields = calloc(fields_count, sizeof(field_method_info_t));
    field_method_info_t field;
    for (size_t i = 0; i < fields_count; i++)
    {
        field.access_flags = read_u2(fptr);
        field.name_index = read_u2(fptr);
        field.descriptor_index = read_u2(fptr);
        field.attributes_count = read_u2(fptr);
        field.attributes = get_attributes(field.attributes_count, fptr);
        fields[i] = field;
    }

    return fields;
}

class_file_t *read_class_file(FILE *fptr)
{
    class_file_t *class_file = malloc(sizeof(class_file_t));

    class_file->magic = read_u4(fptr);
    class_file->minor_version = read_u2(fptr);
    class_file->major_version = read_u2(fptr);
    class_file->constant_pool_count = read_u2(fptr);
    class_file->constant_pool = malloc(sizeof(cp_info_t) * class_file->constant_pool_count);

    // INFO: Quando fazem referencia ao cp_info, precisamos remover um do indice
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
            printf("Current constant pool entry: %i\n", i);
            exit(1);
            break;
        }

        class_file->constant_pool[i] = current_constant_pool;
    }

    class_file->access_flags = read_u2(fptr);
    class_file->this_class = read_u2(fptr);
    class_file->super_class = read_u2(fptr);

    class_file->interfaces_count = read_u2(fptr);
    if (class_file->interfaces_count > 0)
    {
        class_file->interfaces = calloc(class_file->interfaces_count, sizeof(u2_t));
        for (size_t i = 0; i < class_file->interfaces_count; i++)
        {
            class_file->interfaces[i] = read_u2(fptr);
        }
    }

    class_file->fields_count = read_u2(fptr);
    class_file->fields = get_field_method_info(class_file->fields_count, fptr);

    class_file->methods_count = read_u2(fptr);
    class_file->methods = get_field_method_info(class_file->methods_count, fptr);

    class_file->attributes_count = read_u2(fptr);
    class_file->attributes = get_attributes(class_file->attributes_count, fptr);

    return class_file;
}