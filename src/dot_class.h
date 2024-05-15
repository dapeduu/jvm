#include <stdint.h>

typedef unsigned char u1_t;
typedef unsigned short u2_t;
typedef unsigned int u4_t;
typedef unsigned long u8_t; 

typedef struct
{
    u4_t magic;
    u2_t minor_version;
    u2_t major_version;
    u2_t constant_pool_count;
} class_file_t;
