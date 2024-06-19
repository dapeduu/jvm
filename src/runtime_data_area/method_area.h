#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include "../core/core.h"
#include "../core/class.h"

typedef struct {
  class_t* classe;
  hash_table_t* fields_table;
} object_t;

typedef struct {
  hash_table_t loaded_classes;
  object_t* objects;
} method_area_t;

#endif // METHOD_AREA_H