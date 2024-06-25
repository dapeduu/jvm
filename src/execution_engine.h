#ifndef EXECUTION_ENGINE_H
#define EXECUTION_ENGINE_H

#include "core.h"
#include "runtime_data_area.h"

u4_t run_frame(frame_t * frame);

long make_long(uint32_t high, uint32_t low);
float make_float(uint32_t number);
double make_double(uint32_t high, uint32_t low);
uint32_t float_to_uint32(float number);
uint64_t double_to_uint64(double number);

void iand(frame_t * frame);
void land(frame_t * frame);
void irem(frame_t * frame);
void lrem(frame_t * frame);
void frem(frame_t * frame);
void drem_handler(frame_t * frame);
void ixor(frame_t * frame);
void lxor(frame_t * frame);

#endif // EXECUTION_ENGINE_H
