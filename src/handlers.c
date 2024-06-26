#include "core.h"
#include "execution_engine.h"
#include "runtime_data_area.h"
#include <math.h>

float make_float(u4_t number) { return *(float *)&number; }

long make_long(u4_t high, u4_t low) {
  u8_t number;
  number = (((u8_t)high) << 32) | ((u8_t)low);
  return *(long *)&number;
}

double make_double(u4_t high, u4_t low) {
  u8_t number;

  number = (((u8_t)high) << 32) | ((u8_t)low);

  return *(double *)&number;
}

u4_t float_to_uint32(float number) { return *(u4_t *)&number; }

u8_t double_to_uint64(double number) { return *(u8_t *)&number; }

void nop(frame_t *frame) {}

void iload(frame_t *frame) {
  frame->instruction_pointer++;
  u4_t index = frame->code[frame->instruction_pointer];
  // NOTE: pode não sei se esse acesso da certo
  push(frame, frame->locals[index]);
}
void iload_0(frame_t *frame) { push(frame, frame->locals[0]); }
void iload_1(frame_t *frame) { push(frame, frame->locals[1]); }
void iload_2(frame_t *frame) { push(frame, frame->locals[2]); }
void iload_3(frame_t *frame) { push(frame, frame->locals[3]); }

void lload(frame_t *frame) {
  frame->instruction_pointer++;
  u4_t index_hi = frame->code[frame->instruction_pointer];
  u4_t value_hi = frame->locals[index_hi];
  u4_t value_lo = frame->locals[index_hi + 1];

  push(frame, frame->locals[value_hi]);
  push(frame, frame->locals[value_lo]);
}

void lload_0(frame_t *frame) {
  push(frame, frame->locals[0]);
  push(frame, frame->locals[1]);
}

void lload_1(frame_t *frame) {
  push(frame, frame->locals[1]);
  push(frame, frame->locals[2]);
}

void lload_2(frame_t *frame) {
  push(frame, frame->locals[2]);
  push(frame, frame->locals[3]);
}

void lload_3(frame_t *frame) {
  push(frame, frame->locals[3]);
  push(frame, frame->locals[4]);
}

void fload(frame_t *frame) {
  frame->instruction_pointer++;
  u4_t index = frame->instruction_pointer;
  push(frame, frame->locals[index]);
}
void fload_0(frame_t *frame) { push(frame, frame->locals[0]); };
void fload_1(frame_t *frame) { push(frame, frame->locals[1]); };
void fload_2(frame_t *frame) { push(frame, frame->locals[2]); };
void fload_3(frame_t *frame) { push(frame, frame->locals[3]); };

void dload(frame_t *frame) {
  frame->instruction_pointer++;
  u4_t index_hi = frame->instruction_pointer;
  u4_t value_hi = frame->locals[index_hi];
  u4_t value_lo = frame->locals[index_hi + 1];
  push(frame, value_hi);
  push(frame, value_lo);
};

void dload_0(frame_t *frame) {
  push(frame, frame->locals[0]);
  push(frame, frame->locals[1]);
};

void dload_1(frame_t *frame) {
  push(frame, frame->locals[1]);
  push(frame, frame->locals[2]);
};

void dload_2(frame_t *frame) {
  push(frame, frame->locals[2]);
  push(frame, frame->locals[3]);
};

void dload_3(frame_t *frame) {
  push(frame, frame->locals[3]);
  push(frame, frame->locals[4]);
};

void aload(frame_t *frame) {
  frame->instruction_pointer++;
  u4_t index = frame->instruction_pointer;
};
void aload_0(frame_t *frame) { push(frame, frame->locals[0]); };
void aload_1(frame_t *frame) { push(frame, frame->locals[1]); };
void aload_2(frame_t *frame) { push(frame, frame->locals[2]); };
void aload_3(frame_t *frame) { push(frame, frame->locals[3]); };

void iadd(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  push(frame, value1 + value2);
}

void ladd(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);

  long value1 = make_long(value1_hi, value1_lo);
  long value2 = make_long(value2_hi, value2_lo);
  long res = value1 + value2;

  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;

  push(frame, res_hi);
  push(frame, res_lo);
}

void iand(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  u4_t res = value1 &= value2;
  push(frame, res);
};

void land(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);

  long value1 = make_long(value1_hi, value1_lo);
  long value2 = make_long(value2_hi, value2_lo);
  long res = value1 &= value2;

  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;

  push(frame, res_hi);
  push(frame, res_lo);
};

void irem(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  u4_t res = value1 % value2;
  // if value2 == 0 ArithmeticException
  push(frame, res);
}

void lrem(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);

  long value1 = make_long(value1_hi, value1_lo);
  long value2 = make_long(value2_hi, value2_lo);
  // if value2 == 0 ArithmeticException

  u8_t res = value1 % value2;
  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;

  push(frame, res_hi);
  push(frame, res_lo);
}

void frem(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);

  float res = fmod(make_float(value1), make_float(value2));

  push(frame, float_to_uint32(res));
}

// drem teria conflito de nome com função em math.h
void drem_handler(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);

  u8_t value1 = make_double(value1_hi, value1_lo);
  u8_t value2 = make_double(value2_hi, value2_lo);

  u8_t res = double_to_uint64(fmod(value1, value2));
  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;

  push(frame, res_hi);
  push(frame, res_lo);
}

void ixor(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  u4_t res = value1 ^= value2;
  push(frame, res);
};

void lxor(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);

  long value1 = make_long(value1_hi, value1_lo);
  long value2 = make_long(value2_hi, value2_lo);
  long res = value1 ^= value2;

  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;

  push(frame, res_hi);
  push(frame, res_lo);
};

void ireturn(frame_t *frame) {
  // TODO
}
