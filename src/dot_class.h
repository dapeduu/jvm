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
    struct { u2_t name_index; } class;

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

typedef struct
{
  u4_t magic;
  u2_t minor_version;
  u2_t major_version;
  u2_t constant_pool_count;
  cp_info_t * constant_pool;
} class_file_t;
