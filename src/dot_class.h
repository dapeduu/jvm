#include <stdint.h>

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
    } Class;

    // Tag: 7
    struct
    {
      u2_t class_index;
      u2_t name_and_type_index;
    } Fieldref;

    // Tag: 10
    struct
    {
      u2_t class_index;
      u2_t name_and_type_index;
    } Methodref;

  } info;

} cp_info_t;

typedef struct
{
  u4_t magic;
  u2_t minor_version;
  u2_t major_version;
  u2_t constant_pool_count;
  cp_info_t constant_pool[];
} class_file_t;
