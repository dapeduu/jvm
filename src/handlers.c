#include "core.h"
#include "execution_engine.h"
#include "runtime_data_area.h"
#include <math.h>

float make_float(u4_t number) { return *(float *)&number; }

long make_long(u4_t high, u4_t low) {
  u8_t number;
  number = (((u8_t)high) << 32) | ((u8_t)low);
  return *(long long *)&number;
}

double make_double(u4_t high, u4_t low) {
  u8_t number;

  number = (((u8_t)high) << 32) | ((u8_t)low);

  return *(double *)&number;
}

u4_t float_to_uint32(float number) { return *(u4_t *)&number; }

u8_t double_to_uint64(double number) { return *(u8_t *)&number; }
u8_t long_to_uint64(long long number) { return *(u8_t *)&number; }

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
  push(frame, frame->locals[index]);
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

void fadd(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  float res = make_float(value1) + make_float(value2);
  push(frame, float_to_uint32(res));
}

void ladd(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);

  long long value1 = make_long(value1_hi, value1_lo);
  long long value2 = make_long(value2_hi, value2_lo);
  long long res = value1 + value2;

  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;

  push(frame, res_hi);
  push(frame, res_lo);
}

void dadd(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);
  double value1 = make_double(value1_hi, value1_lo);
  double value2 = make_double(value2_hi, value2_lo);

  u8_t res = double_to_uint64(value1 + value2);
  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)(res & 0x00000000FFFFFFFF);
  push(frame, res_hi);
  push(frame, res_lo);
}

void isub(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  push(frame, value1 - value2);
}

void fsub(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  float res = make_float(value1) - make_float(value2);
  push(frame, float_to_uint32(res));
}

void lsub(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);

  long long value1 = make_long(value1_hi, value1_lo);
  long long value2 = make_long(value2_hi, value2_lo);
  long long res = value1 - value2;

  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;

  push(frame, res_hi);
  push(frame, res_lo);
}

void dsub(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);
  double value1 = make_double(value1_hi, value1_lo);
  double value2 = make_double(value2_hi, value2_lo);

  u8_t res = double_to_uint64(value1 - value2);
  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)(res & 0x00000000FFFFFFFF);
  push(frame, res_hi);
  push(frame, res_lo);
}

void idiv(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  push(frame, value1 / value2);
}

void ldiv_handler(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);
  long long value1 = make_long(value1_hi, value1_lo);
  long long value2 = make_long(value2_hi, value2_lo);

  u8_t res = long_to_uint64(value1 / value2);
  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)(res & 0x00000000FFFFFFFF);
  push(frame, res_hi);
  push(frame, res_lo);
}

void fdiv(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  u4_t result = make_float(value1) / make_float(value2);
  push(frame, float_to_uint32(result));
}

void ddiv(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);
  double value1 = make_double(value1_hi, value1_lo);
  double value2 = make_double(value2_hi, value2_lo);

  u8_t res = double_to_uint64(value1 / value2);
  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)(res & 0x00000000FFFFFFFF);
  push(frame, res_hi);
  push(frame, res_lo);
}

void imul(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  push(frame, value1 * value2);
}

void lmul(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);

  long long value1 = make_long(value1_hi, value1_lo);
  long long value2 = make_long(value2_hi, value2_lo);
  u8_t res = long_to_uint64(value1 * value2);
  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;
  push(frame, res_hi);
  push(frame, res_lo);
}

void fmul(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  push(frame, make_float(value1) * make_float(value2));
}

void dmul(frame_t *frame) {
  u4_t value1_hi = pop(frame);
  u4_t value1_lo = pop(frame);
  u4_t value2_hi = pop(frame);
  u4_t value2_lo = pop(frame);

  double value1 = make_double(value1_hi, value1_lo);
  double value2 = make_double(value2_hi, value2_lo);
  u8_t res = double_to_uint64(value1 * value2);
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

  long long value1 = make_long(value1_hi, value1_lo);
  long long value2 = make_long(value2_hi, value2_lo);
  long long res = value1 &= value2;

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

  long long value1 = make_long(value1_hi, value1_lo);
  long long value2 = make_long(value2_hi, value2_lo);
  long long res = value1 ^= value2;

  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;

  push(frame, res_hi);
  push(frame, res_lo);
};

void ireturn(frame_t *frame) {
  // TODO
}

void ineg(frame_t *frame) {
  u4_t value = pop(frame);
  push(frame, -value);
}

void lneg(frame_t *frame) {
  u4_t value_hi = pop(frame);
  u4_t value_lo = pop(frame);

  long long value = make_long(value_hi, value_lo);
  long long res = -value;

  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;

  push(frame, res_hi);
  push(frame, res_lo);
}

void fneg(frame_t *frame) {
  u4_t value = pop(frame);
  float res = -make_float(value);
  push(frame, float_to_uint32(res));
}

void dneg(frame_t *frame) {
  u4_t value_hi = pop(frame);
  u4_t value_lo = pop(frame);

  u8_t value = make_double(value_hi, value_lo);
  u8_t res = -value;

  u4_t res_hi = (u4_t)(res >> 32) & 0x00000000FFFFFFFF;
  u4_t res_lo = (u4_t)res & 0x00000000FFFFFFFF;

  push(frame, res_hi);
  push(frame, res_lo);
}

void iconst_m1(frame_t *frame) { push(frame, -1); }
void iconst_0(frame_t *frame) { push(frame, 0); }
void iconst_1(frame_t *frame) { push(frame, 1); }
void iconst_2(frame_t *frame) { push(frame, 2); }
void iconst_3(frame_t *frame) { push(frame, 3); }
void iconst_4(frame_t *frame) { push(frame, 4); }
void iconst_5(frame_t *frame) { push(frame, 5); }

void bipush(frame_t *frame) {
  frame->instruction_pointer++;
  u1_t value = frame->code[frame->instruction_pointer];
  push(frame, (u4_t)value);
}

void pop_op(frame_t *frame) { pop(frame); }

void invokestatic(frame_t *frame) {
  frame->instruction_pointer++;
  u1_t indexbyte1 = frame->code[frame->instruction_pointer];
  frame->instruction_pointer++;
  u1_t indexbyte2 = frame->code[frame->instruction_pointer];

  u2_t index = (indexbyte1 << 8) | indexbyte2;

  cp_info_t method_ref = frame->class_data->constant_pool[index - 1];

  cp_info_t class_index =
      frame->class_data
          ->constant_pool[method_ref.info.methodref.class_index - 1];
  cp_info_t class_utf8_index =
      frame->class_data->constant_pool[class_index.info.class.name_index - 1];
  char *class_name = get_constant_pool_value(frame->class_data->constant_pool,
                                             class_index.info.class.name_index);

  cp_info_t method_utf8_index =
      frame->class_data->constant_pool[class_index.info.methodref.name_and_type_index - 1];
  char *method_name = get_constant_pool_value(frame->class_data->constant_pool,
                                             method_utf8_index.info.name_and_type.name_index);

  printf("class name: %s\n", class_name);
  printf("method name: %s\n", method_name);

  // TODO: 
  //  - carregar a classe
  //  - inicializar classe
  //  - montar o frame do método
  //  - carregar valores da pilha de operandos do frame atual para as variaveis locais do frame novo
  //  - empilhar frame novo
  //  - setar pc da jvm (?) para o opcode da primeira instrução do frame novo

  // cp_info_t name_and_type_index = frame->class_data->constant_pool[
  //   method_ref.info.methodref.name_and_type_index - 1
  // ];

  // u1_t index_hi = frame->instruction_pointer;
  // u4_t value_hi = frame->locals[index_hi];
  // u4_t value_lo = frame->locals[index_hi + 1];
}
