#ifndef CORE_H
#define CORE_H

#include <stdint.h>

// Base types
typedef uint8_t u1_t;
typedef uint16_t u2_t;
typedef uint32_t u4_t;
typedef uint64_t u8_t;

// Constant pool values
#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1

#endif // CORE_H