#ifndef HANDLERS_H
#define HANDLERS_H

#include "core.h"
#include "runtime_data_area.h"

long make_long(u4_t high, u4_t low);
float make_float(u4_t number);
double make_double(u4_t high, u4_t low);
u4_t float_to_uint32(float number);
u8_t double_to_uint64(double number);

void iand(frame_t * frame);
void land(frame_t * frame);
void irem(frame_t * frame);
void lrem(frame_t * frame);
void frem(frame_t * frame);
void drem_handler(frame_t * frame);
void ixor(frame_t * frame);
void lxor(frame_t * frame);


#endif // HANDLERS_H
