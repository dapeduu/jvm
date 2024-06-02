#include <stdio.h>
#include <stdlib.h>
#include "./core/core.h"
#include "./core/consts.h"

int main(int argc, char *argv[])
{
    FILE *fptr;
    fptr = fopen(argv[1], "rb");
    if (fptr == NULL)
    {
        printf("Not able to open the file.\n");
        return 1;
    }

    printf("\n============ %s ============\n", argv[1]);

    class_file_t *class_file = read_class_file(fptr);

    printf("magic: %x\n", class_file->magic);
    printf("minor_version: %i\n", class_file->minor_version);
    printf("major_version: %i\n", class_file->major_version);
    printf("constant_pool_count: %i\n", class_file->constant_pool_count - 1);

    printf("\n### Constant Pool ###\n");
    for (size_t i = 0; i < class_file->constant_pool_count - 1; i++)
    {
        printf("[%zu] Tag: %u\n", i, class_file->constant_pool[i].tag);
        switch (class_file->constant_pool[i].tag)
        {
        case CONSTANT_Class:
            printf("Class name index: %u\n", class_file->constant_pool[i].info.class.name_index);
            break;
        case CONSTANT_Fieldref:
            printf("Fieldref class index: %u, name and type index: %u\n",
                   class_file->constant_pool[i].info.fieldref.class_index,
                   class_file->constant_pool[i].info.fieldref.name_and_type_index);
            break;
        case CONSTANT_Methodref:
            printf("Methodref class index: %u, name and type index: %u\n",
                   class_file->constant_pool[i].info.methodref.class_index,
                   class_file->constant_pool[i].info.methodref.name_and_type_index);
            break;
        case CONSTANT_InterfaceMethodref:
            printf("InterfaceMethodref class index: %u, name and type index: %u\n",
                   class_file->constant_pool[i].info.interface_methodref.class_index,
                   class_file->constant_pool[i].info.interface_methodref.name_and_type_index);
            break;
        case CONSTANT_String:
            printf("String index: %u\n", class_file->constant_pool[i].info.string.string_index);
            break;
        case CONSTANT_Integer:
            printf("Integer bytes: %u\n", class_file->constant_pool[i].info.integer.bytes);
            break;
        case CONSTANT_Float:
            printf("Float bytes: %u\n", class_file->constant_pool[i].info.float_num.bytes);
            break;
        case CONSTANT_Long:
            printf("Long high bytes: %u, low bytes: %u\n",
                   class_file->constant_pool[i].info.long_num.high_bytes,
                   class_file->constant_pool[i].info.long_num.low_bytes);
            break;
        case CONSTANT_Double:
            printf("Double high bytes: %u, low bytes: %u\n",
                   class_file->constant_pool[i].info.double_num.high_bytes,
                   class_file->constant_pool[i].info.double_num.low_bytes);
            break;
        case CONSTANT_NameAndType:
            printf("NameAndType name index: %u, descriptor index: %u\n",
                   class_file->constant_pool[i].info.name_and_type.name_index,
                   class_file->constant_pool[i].info.name_and_type.descriptor_index);
            break;
        case CONSTANT_Utf8:
            printf("UTF8 length: %u, string: %s\n",
                   class_file->constant_pool[i].info.utf8.length_of_byte_array,
                   class_file->constant_pool[i].info.utf8.string);
            break;
        default:
            printf("Unhandled constant pool tag: %u\n", class_file->constant_pool[i].tag);
            break;
        }
    }
    printf("### End Constant Pool ###\n\n");

    printf("access_flags: 0x%04x\n", class_file->access_flags);
    printf("this_class: cp_info #%i\n", class_file->this_class);
    printf("super_class: cp_info #%i\n", class_file->super_class);

    printf("\n### Interfaces ###\n");
    printf("interfaces_count: %i\n", class_file->interfaces_count);

    if (class_file->interfaces_count > 0)
    {
        for (size_t i = 0; i <= class_file->interfaces_count - 1; i++)
        {
            printf("[%li] Interface: cp_info #%i\n", i, class_file->interfaces[i]);
        }
    }
    printf("### End Interfaces ###\n\n");

    printf("\n### Fields ###\n");
    printf("fields_count: %i\n", class_file->fields_count);
    for(size_t i = 0; i < class_file->fields_count; i++) {
        printf("Field #%zu\n", i);
        printf("access_flags: 0x%04x\n", class_file->fields[i].access_flags);
        printf("name_index: cp_info #%i\n", class_file->fields[i].name_index);
        printf("descriptor_index: cp_info #%i\n", class_file->fields[i].descriptor_index);
        printf("attributes_count: %i\n", class_file->fields[i].attributes_count);
        
        printf("\n### Attributes ###\n");
        for(size_t j = 0; j < class_file->fields[i].attributes_count; j++) {
            printf("Attribute #%zu\n", j);
            printf("attribute_name_index: cp_info #%i\n", class_file->fields[i].attributes[j].attribute_name_index);
            printf("attribute_length: %i\n", class_file->fields[i].attributes[j].attribute_length);
            printf("info: ");
            for(size_t k = 0; k < class_file->fields[i].attributes[j].attribute_length; k++) {
                printf("%02x ", class_file->fields[i].attributes[j].info[k]);
            }
            printf("\n");
        }
        printf("### End Attributes ###\n\n");
    }
    printf("### End Fields ###\n\n");

    printf("\n### Methods ###\n");
    printf("methods_count: %i\n", class_file->methods_count);
    for(size_t i = 0; i < class_file->methods_count; i++) {
        printf("Method #%zu\n", i);
        printf("access_flags: 0x%04x\n", class_file->methods[i].access_flags);
        printf("name_index: cp_info #%i\n", class_file->methods[i].name_index);
        printf("descriptor_index: cp_info #%i\n", class_file->methods[i].descriptor_index);
        printf("attributes_count: %i\n", class_file->methods[i].attributes_count);

        printf("\n### Attributes (Method %zu) ###\n", i);
        for(size_t j = 0; j < class_file->methods[i].attributes_count; j++) {
            printf("Attribute #%zu\n", j);
            printf("attribute_name_index: cp_info #%i\n", class_file->methods[i].attributes[j].attribute_name_index);
            printf("attribute_length: %i\n", class_file->methods[i].attributes[j].attribute_length);
            printf("\n");
        }
        printf("### End Attributes ###\n\n");
    }

    printf("### CLASSFILE Attributes ###\n\n");
    printf("attributes_count: %d\n\n", class_file->attributes_count);
    for(size_t i = 0; i < class_file->attributes_count; i++) {
        printf("Attribute #%zu\n", i);
        printf("attribute_name_index: cp_info #%i\n", class_file->attributes[i].attribute_name_index);
        printf("attribute_length: %i\n", class_file->attributes[i].attribute_length);
        printf("\n");
    }
    printf("### End Classfile Attributes ###\n\n");

    free_class_file(class_file);
    fclose(fptr);

    return 0;
}
