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
    if (class_file->interfaces_count > 0) {
        class_file->interfaces = malloc(sizeof(u2_t) * class_file->interfaces_count);
        for (size_t i = 0; i < class_file->interfaces_count; i++)
        {
            class_file->interfaces[i] = read_u2(fptr);
        }
    }

    class_file->fields_count = read_u2(fptr);
    class_file->fields = get_fields(class_file->fields_count, fptr);

    class_file->methods_count = read_u2(fptr);
    class_file->methods = get_methods(class_file->methods_count, fptr);

    class_file->attributes_count = read_u2(fptr);
    class_file->attributes = get_attributes(class_file->attributes_count, fptr);

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

    // Free fields and their attributes
    for (size_t i = 0; i < class_file->fields_count; i++)
    {
        for (size_t j = 0; j < class_file->fields[i].attributes_count; j++)
        {
            free(class_file->fields[i].attributes[j].info);
        }
        free(class_file->fields[i].attributes);
    }
    free(class_file->fields);

    // Free methods and their attributes
    for (size_t i = 0; i < class_file->methods_count; i++)
    {
        for (size_t j = 0; j < class_file->methods[i].attributes_count; j++)
        {
            free(class_file->methods[i].attributes[j].info);
        }
        free(class_file->methods[i].attributes);
    }
    free(class_file->methods);

    // Free class file attributes
    for (size_t i = 0; i < class_file->attributes_count; i++)
    {
        free(class_file->attributes[i].info);
    }
    free(class_file->attributes);

    free(class_file);

    return 0;
}

field_info_t* get_fields(int fields_count, FILE* fptr) {
    field_info_t* fields = malloc(sizeof(field_info_t) * fields_count);
    for (size_t i = 0; i < fields_count; i++) {
        field_info_t field;
        field.access_flags = read_u2(fptr);
        field.name_index = read_u2(fptr);
        field.descriptor_index = read_u2(fptr);
        field.attributes_count = read_u2(fptr);

        field.attributes = get_attributes(field.attributes_count, fptr);

        fields[i] = field;
    }

    return fields;
}

attribute_info_t* get_attributes(int attributes_count, FILE* fptr) {
    attribute_info_t* attributes = malloc(sizeof(attribute_info_t) * attributes_count);
    for (size_t j=0; j<attributes_count;j++) {
        attribute_info_t attribute;
        attribute.attribute_name_index = read_u2(fptr);
        attribute.attribute_length = read_u4(fptr);
        attribute.info = malloc(sizeof(u1_t) * attribute.attribute_length);

        for(size_t k = 0; k < attribute.attribute_length; k++) {
            attribute.info[k] = read_u1(fptr);
        }
        attributes[j] = attribute;
    }
    return attributes;
}

method_info_t* get_methods(int methods_count, FILE* fptr) {
    method_info_t *methods = malloc(sizeof(method_info_t) * methods_count);

    for (size_t i=0; i<methods_count;i++) {
        method_info_t method;
            method.access_flags = read_u2(fptr);
            method.name_index = read_u2(fptr);
            method.descriptor_index = read_u2(fptr);
            method.attributes_count = read_u2(fptr);

            //TALVEZ ESTEJA ERRADO
            method.attributes = get_attributes(method.attributes_count, fptr);
            methods[i] = method;
    }
    return methods;
}


