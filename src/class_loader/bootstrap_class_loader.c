#include "../core/class.h"
#include "../runtime_data_area/method_area.h"

class_t * load_class_file(class_file_t *classfile) {
    printf("Magic: 0x%X\n", classfile->magic);  
    printf("Minor Version: %0x\n", classfile->minor_version);
    printf("Major Version: %u\n", classfile->major_version);
    printf("Constant Pool Count: %u\n", classfile->constant_pool_count);
  return NULL;
}