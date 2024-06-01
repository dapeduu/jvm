#include "core.h"

u1_t read_u1(FILE *fptr)
{
    u1_t value;

    value = getc(fptr);

    return value;
}

u2_t read_u2(FILE *fptr)
{
    u2_t value;
    u1_t buffer[2];

    fread(buffer, sizeof(u1_t), 2, fptr);

    value = (buffer[0] << 8) | buffer[1];

    return value;
}

u4_t read_u4(FILE *fptr)
{
    u4_t value;
    u1_t buffer[4];

    fread(buffer, sizeof(u1_t), 4, fptr);

    value = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];

    return value;
}