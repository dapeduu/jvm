#ifndef EXECUTION_ENGINE_H
#define EXECUTION_ENGINE_H

#include "core.h"
#include "runtime_data_area.h"

void push(frame_t * frame, u4_t argument);
u4_t pop(frame_t * frame);
u4_t run_frame(frame_t * frame);


#endif // EXECUTION_ENGINE_H
