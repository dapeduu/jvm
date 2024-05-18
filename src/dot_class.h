#include <stdint.h>

typedef uint8_t u1_t;
typedef uint16_t u2_t;
typedef uint32_t u4_t;
// typedef unsigned long u8_t; N será possível ler u8 com 32bits 

typedef struct
{
    u4_t magic;
    u2_t minor_version;
    u2_t major_version;
    u2_t constant_pool_count;
} class_file_t;
