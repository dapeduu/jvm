/**
 * @file handlers.c
 * @brief Implementação das funções de manipulação de dados.
 * Declara funções para converter tipos de dados, e contém a implementação das funções 
 * gerais da JVM, como iload, lload, fload, dload, nop, iadd, etc.
 */

#include <math.h>
#include <stdlib.h>
#include "core.h"
#include "execution_engine.h"
#include "runtime_data_area.h"

/**
 * @brief make_float
 * Converte um 32-bit unsigned integer para float.
 * @param number 
 * @return float 
 */
float make_float(u4_t number) { return *(float *)&number; }

/**
 * @brief make_long
 * Converte dois 32-bit unsigned integers para long.
 * @param high 
 * @param low 
 * @return long long 
 */
long make_long(u4_t high, u4_t low) {
  u8_t number;
  number = (((u8_t)high) << 32) | ((u8_t)low);
  return *(long long *)&number;
}

/**
 * @brief make_double
 * Converte dois 32-bit unsigned integers para double.
 * @param high 
 * @param low 
 * @return double 
 */
double make_double(u4_t high, u4_t low) {
  u8_t number;

  number = (((u8_t)high) << 32) | ((u8_t)low);

  return *(double *)&number;
}

/**
 * @brief float_to_uint32
 * Converte um float para 32-bit unsigned integer.
 * @param number 
 * @return u4_t 
 */
u4_t float_to_uint32(float number) { return *(u4_t *)&number; }

/**
 * @brief double_to_uint64
 * Converte um double para 64-bit unsigned integer.
 * @param number 
 * @return u8_t 
 */
u8_t double_to_uint64(double number) { return *(u8_t *)&number; }

/**
 * @brief long_to_uint64
 * Converte long para 64-bit unsigned integer.
 * @param number 
 * @return u8_t 
 */
u8_t long_to_uint64(long long number) { return *(u8_t *)&number; }

/**
 * @brief nop
 * Não faz nada.
 * @param frame 
 * @return void
 */
void nop(frame_t *frame) {}

/**
 * @brief iload
 * Carrega um inteiro de uma variável local.
 * @param frame 
 * @return void
 */
void iload(frame_t *frame) {
  frame->instruction_pointer++;
  u4_t index = frame->code[frame->instruction_pointer];
  // NOTE: pode não sei se esse acesso da certo
  push(frame, frame->locals[index]);
}

/**
 * @brief iload_0
 * Carrega um inteiro da primeira variável local.
 * @param frame 
 * @return void
 */
void iload_0(frame_t *frame) { push(frame, frame->locals[0]); }

/**
 * @brief iload_1
 * Carrega um inteiro da segunda variável local.
 * @param frame 
 * @return void
 */
void iload_1(frame_t *frame) { push(frame, frame->locals[1]); }

/**
 * @brief iload_2
 * Carrega um inteiro da terceira variável local.
 * @param frame 
 * @return void
 */
void iload_2(frame_t *frame) { push(frame, frame->locals[2]); }

/**
 * @brief iload_3
 * Carrega um inteiro da quarta variável local.
 * @param frame 
 * @return void
 */
void iload_3(frame_t *frame) { push(frame, frame->locals[3]); }

/**
 * @brief lload
 * Carrega um long de uma variável local.
 * @param frame 
 * @return void
 */
void lload(frame_t *frame) {
  frame->instruction_pointer++;
  u4_t index_hi = frame->code[frame->instruction_pointer];
  u4_t value_hi = frame->locals[index_hi];
  u4_t value_lo = frame->locals[index_hi + 1];

  push(frame, frame->locals[value_hi]);
  push(frame, frame->locals[value_lo]);
}

/**
 * @brief lload_0
 * Carrega um long da primeira variável local
 * @param frame 
 * @return void
 */
void lload_0(frame_t *frame) {
  push(frame, frame->locals[0]);
  push(frame, frame->locals[1]);
}

/**
 * @brief lload_1
 * Carrega um long da segunda variável local.
 * @param frame 
 * @return void
 */
void lload_1(frame_t *frame) {
  push(frame, frame->locals[1]);
  push(frame, frame->locals[2]);
}

/**
 * @brief lload_2
 * Carrega um long da terceira variável local.
 * @param frame 
 * @return void
 */
void lload_2(frame_t *frame) {
  push(frame, frame->locals[2]);
  push(frame, frame->locals[3]);
}

/**
 * @brief lload_3
 * Carrega um long da quarta variável local.
 * @param frame 
 * @return void
 */
void lload_3(frame_t *frame) {
  push(frame, frame->locals[3]);
  push(frame, frame->locals[4]);
}

/**
 * @brief fload
 * Carrega um float de uma variável local.
 * @param frame 
 * @return void
 */
void fload(frame_t *frame) {
  frame->instruction_pointer++;
  u4_t index = frame->instruction_pointer;
  push(frame, frame->locals[index]);
}

/**
 * @brief fload_0
 * Carrega um float da primeira variável local.
 * @param frame 
 * @return void
 */
void fload_0(frame_t *frame) { push(frame, frame->locals[0]); };

/**
 * @brief fload_1
 * Carrega um float da segunda variável local.
 * @param frame 
 * @return void
 */
void fload_1(frame_t *frame) { push(frame, frame->locals[1]); };

/**
 * @brief fload_2
 * Carrega um float da terceira variável local.
 * @param frame 
 * @return void
 */
void fload_2(frame_t *frame) { push(frame, frame->locals[2]); };

/**
 * @brief fload_3
 * Carrega um float da quarta variável local.
 * @param frame 
 * @return void
 */
void fload_3(frame_t *frame) { push(frame, frame->locals[3]); };

/**
 * @brief dload
 * Carrega um double de uma variável local.
 * @param frame 
 * @return void
 */
void dload(frame_t *frame) {
  frame->instruction_pointer++;
  u4_t index_hi = frame->instruction_pointer;
  u4_t value_hi = frame->locals[index_hi];
  u4_t value_lo = frame->locals[index_hi + 1];
  push(frame, value_hi);
  push(frame, value_lo);
};


/**
 * @brief dload_0
 * Carrega um double da primeira variável local.
 * @param frame 
 * @return void
 */
void dload_0(frame_t *frame) {
  push(frame, frame->locals[0]);
  push(frame, frame->locals[1]);
};

/**
 * @brief dload_1
 * Carrega um double da segunda variável local.
 * @param frame 
 * @return void
 */
void dload_1(frame_t *frame) {
  push(frame, frame->locals[1]);
  push(frame, frame->locals[2]);
};

/**
 * @brief dload_2
 * Carrega um double da terceira variável local.
 * @param frame 
 * @return void
 */
void dload_2(frame_t *frame) {
  push(frame, frame->locals[2]);
  push(frame, frame->locals[3]);
};

/**
 * @brief dload_3
 * Carrega um double da quarta variável local.
 * @param frame 
 * @return void
 */
void dload_3(frame_t *frame) {
  push(frame, frame->locals[3]);
  push(frame, frame->locals[4]);
};

/**
 * @brief aload
 * Carrega uma referência de uma variável local.
 * @param frame 
 * @return void
 */
void aload(frame_t *frame) {
  frame->instruction_pointer++;
  u4_t index = frame->instruction_pointer;
  push(frame, frame->locals[index]);
};

/**
 * @brief aload_0
 * Carrega uma referência da primeira variável local.
 * @param frame 
 * @return void
 */
void aload_0(frame_t *frame) { push(frame, frame->locals[0]); };

/**
 * @brief aload_1
 * Carrega uma referência da segunda variável local.
 * @param frame 
 * @return void
 */
void aload_1(frame_t *frame) { push(frame, frame->locals[1]); };

/**
 * @brief aload_2
 * Carrega uma referência da terceira variável local.
 * @param frame 
 * @return void
 */
void aload_2(frame_t *frame) { push(frame, frame->locals[2]); };

/**
 * @brief aload_3
 * Carrega uma referência da quarta variável local.
 * @param frame 
 * @return void
 */
void aload_3(frame_t *frame) { push(frame, frame->locals[3]); };

/**
 * @brief iadd
 * Soma dois inteiros e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void iadd(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  push(frame, value1 + value2);
}

/**
 * @brief fadd
 * Soma dois floats e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void fadd(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  float res = make_float(value1) + make_float(value2);
  push(frame, float_to_uint32(res));
}

/**
 * @brief ladd
 * Soma dois longs e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
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

/**
 * @brief dadd
 * Soma dois doubles e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
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

/**
 * @brief isub
 * Subtrai dois inteiros e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void isub(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  push(frame, value1 - value2);
}

/**
 * @brief fsub
 * Subtrai dois floats e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void fsub(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  float res = make_float(value1) - make_float(value2);
  push(frame, float_to_uint32(res));
}

/**
 * @brief lsub
 * Subtrai dois longs e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
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

/**
 * @brief dsub
 * Subtrai dois doubles e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
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

/**
 * @brief idiv
 * Divide dois inteiros e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void idiv(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  push(frame, value1 / value2);
}

/**
 * @brief fdiv_handler
 * Lida com a divisão de longs.
 * @param frame
 * @return void
 */
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

/**
 * @brief fdiv
 * Divide dois floats e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void fdiv(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  u4_t result = make_float(value1) / make_float(value2);
  push(frame, float_to_uint32(result));
}

/**
 * @brief ddiv
 * Divide dois doubles e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
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

/**
 * @brief imul
 * Multiplica dois inteiros e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void imul(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  push(frame, value1 * value2);
}

/**
 * @brief lmul
 * Multiplica dois longs e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
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

/**
 * @brief fmul
 * Multiplica dois floats e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void fmul(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  push(frame, make_float(value1) * make_float(value2));
}

/**
 * @brief dmul
 * Multiplica dois doubles e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
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

/**
 * @brief idiv
 * Divide dois inteiros e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void iand(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  u4_t res = value1 &= value2;
  push(frame, res);
};

/**
 * @brief land
 * Faz a operação AND entre dois longs e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
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

/**
 * @brief irem
 * Calcula o resto da divisão de dois inteiros e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void irem(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  u4_t res = value1 % value2;
  // if value2 == 0 ArithmeticException
  push(frame, res);
}

/**
 * @brief lrem
 * Calcula o resto da divisão de dois longs e coloca o resultado na pilha.
 * 
 * @param frame 
 * @return void
 */
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

/**
 * @brief frem
 * Calcula o resto da divisão de dois floats e coloca o resultado na pilha.
 * 
 * @param frame 
 * @return void
 */
void frem(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);

  float res = fmod(make_float(value1), make_float(value2));

  push(frame, float_to_uint32(res));
}

// drem teria conflito de nome com função em math.h
/**
 * @brief drem_handler
 * Calcula o resto da divisão de dois doubles e coloca o resultado na pilha.
 * É o equivalente a drem, mas com outro nome para evitar conflito.
 * 
 * @param frame 
 * @return void
 */
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

/**
 * @brief ixor
 * Faz a operação XOR entre dois inteiros e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
void ixor(frame_t *frame) {
  u4_t value1 = pop(frame);
  u4_t value2 = pop(frame);
  u4_t res = value1 ^= value2;
  push(frame, res);
};

/**
 * @brief lxor
 * Faz a operação XOR entre dois longs e coloca o resultado na pilha.
 * @param frame
 * @return void
 */
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

/**
 * @brief ineg
 * Inverte o sinal de um inteiro e coloca o resultado na pilha.
 * 
 * @param frame 
 * @return void
 */
void ineg(frame_t *frame) {
  u4_t value = pop(frame);
  push(frame, -value);
}

/**
 * @brief lneg
 * Inverte o sinal de um long e coloca o resultado na pilha.
 * 
 * @param frame 
 * @return void
 */
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

/**
 * @brief fneg
 * Inverte o sinal de um float e coloca o resultado na pilha.
 * 
 * @param frame 
 * @return void
 */
void fneg(frame_t *frame) {
  u4_t value = pop(frame);
  float res = -make_float(value);
  push(frame, float_to_uint32(res));
}

/**
 * @brief dneg
 * Inverte o sinal de um double e coloca o resultado na pilha.
 * 
 * @param frame 
 * @return void
 */
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

/**
 * @brief iconst_m1
 * Coloca o valor -1 na pilha.
 * 
 * @param frame 
 * @return void
 */
void iconst_m1(frame_t *frame) { push(frame, -1); }

/**
 * @brief iconst_0
 * Coloca o valor 0 na pilha.
 * 
 * @param frame 
 * @return void
 */
void iconst_0(frame_t *frame) { push(frame, 0); }

/**
 * @brief iconst_1
 * Coloca o valor 1 na pilha.
 * 
 * @param frame 
 * @return void
 */
void iconst_1(frame_t *frame) { push(frame, 1); }

/**
 * @brief iconst_2
 * Coloca o valor 2 na pilha.
 * 
 * @param frame 
 * @return void
 */
void iconst_2(frame_t *frame) { push(frame, 2); }

/**
 * @brief iconst_3
 * Coloca o valor 3 na pilha.
 * 
 * @param frame 
 * @return void
 */
void iconst_3(frame_t *frame) { push(frame, 3); }

/**
 * @brief iconst_4
 * Coloca o valor 4 na pilha.
 * 
 * @param frame 
 * @return void
 */
void iconst_4(frame_t *frame) { push(frame, 4); }

/**
 * @brief iconst_5
 * Coloca o valor 5 na pilha.
 * 
 * @param frame 
 * @return void
 */
void iconst_5(frame_t *frame) { push(frame, 5); }

/**
 * @brief bipush
 * Coloca um byte na pilha.
 * 
 * @param frame 
 * @return void
 */
void bipush(frame_t *frame) {
  frame->instruction_pointer++;
  u1_t value = frame->code[frame->instruction_pointer];
  push(frame, (u4_t)value);
}

/**
 * @brief pop_op
 * Remove um valor do topo da pilha.
 * 
 * @param frame 
 * @return void
 */
void pop_op(frame_t *frame) { pop(frame); }

/**
 * @brief invokestatic
 * Invoca um método estático.
 * 
 * @param frame 
 * @return void
 */
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
  char *type = get_constant_pool_value(frame->class_data->constant_pool,
                                             method_utf8_index.info.name_and_type.descriptor_index);


  printf("class name: %s\n", class_name);
  printf("method name: %s\n", method_name);
  printf("type: %s\n", type);

  // Carregar os argumentos

  int args_count = 2;
  u4_t * args = malloc(sizeof(u4_t) * args_count);
  for (size_t i = 0; i < args_count; i++)
  {
    args[i] = pop(frame);
    printf("args[%i]: %i\n", i, args[i]);
  }

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
