#ifndef CLASS_H
#define CLASS_H

#include "core.h"

typedef enum {
  unloaded,
  loading,
  loaded,
  initializing,
  initialized,
  error
} class_status_t;

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
  class_status_t status;
  hash_table_t *methods_table;
  hash_table_t *fields_table;
} class_t;

#endif // CLASS_H