#include "./core/core.h"

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
  u2_t * interfaces;
  u2_t fields_count;
  field_info_t *fields;
  u2_t attributes_count;
  attribute_info_t *attributes;
  u2_t methods_count;
  method_info_t *methods;
  // TODO: adapt this to class_t instead of class_file_t
} class_t;
