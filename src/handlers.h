#ifndef HANDLERS_H
#define HANDLERS_H

#include "core.h"
#include "runtime_data_area.h"

long make_long(u4_t high, u4_t low);
float make_float(u4_t number);
double make_double(u4_t high, u4_t low);
u4_t float_to_uint32(float number);
u8_t double_to_uint64(double number);

void nop(frame_t *frame);
void iload(frame_t *frame);
void iload_0(frame_t *frame);
void iload_1(frame_t *frame);
void iload_2(frame_t *frame);
void iload_3(frame_t *frame);
void lload(frame_t *frame);
void lload_0(frame_t *frame);
void lload_1(frame_t *frame);
void lload_2(frame_t *frame);
void lload_3(frame_t *frame);
void fload(frame_t *frame);
void fload_0(frame_t *frame);
void fload_1(frame_t *frame);
void fload_2(frame_t *frame);
void fload_3(frame_t *frame);
void dload(frame_t *frame);
void dload_0(frame_t *frame);
void dload_1(frame_t *frame);
void dload_2(frame_t *frame);
void dload_3(frame_t *frame);
void aload(frame_t *frame);
void aload_0(frame_t *frame);
void aload_1(frame_t *frame);
void aload_2(frame_t *frame);
void aload_3(frame_t *frame);
void iadd(frame_t *frame);
void ladd(frame_t *frame);
void fadd(frame_t *frame);
void dadd(frame_t *frame);
void iand(frame_t *frame);
void land(frame_t *frame);
void irem(frame_t *frame);
void lrem(frame_t *frame);
void frem(frame_t *frame);
void drem_handler(frame_t *frame);
void ixor(frame_t *frame);
void lxor(frame_t *frame);
void ireturn(frame_t *frame);
void ineg(frame_t *frame);
void lneg(frame_t *frame);
void fneg(frame_t *frame);
void dneg(frame_t *frame);
void iconst_m1(frame_t *frame);
void iconst_0(frame_t *frame);
void iconst_1(frame_t *frame);
void iconst_2(frame_t *frame);
void iconst_3(frame_t *frame);
void iconst_4(frame_t *frame);
void iconst_5(frame_t *frame);
void bipush(frame_t *frame);
void invokestatic(frame_t *frame);
void pop_op(frame_t *frame);
void imul(frame_t *frame);
void fmul(frame_t *frame);
void lmul(frame_t *frame);
void dmul(frame_t *frame);
void idiv(frame_t *frame);
void ldiv_handler(frame_t *frame);
void fdiv(frame_t *frame);
void ddiv(frame_t *frame);


void (*inst_vector[256])(frame_t *) = {
    /* 0x00 (0) */ nop,
    /* 0x01 (1) */ NULL,
    /* 0x02 (2) */ iconst_m1,
    /* 0x03 (3) */ iconst_0,
    /* 0x04 (4) */ iconst_1,
    /* 0x05 (5) */ iconst_2,
    /* 0x06 (6) */ iconst_3,
    /* 0x07 (7) */ iconst_4,
    /* 0x08 (8) */ iconst_5,
    /* 0x09 (9) */ NULL,
    /* 0x0a (10) */ NULL,
    /* 0x0b (11) */ NULL,
    /* 0x0c (12) */ NULL,
    /* 0x0d (13) */ NULL,
    /* 0x0e (14) */ NULL,
    /* 0x0f (15) */ NULL,
    /* 0x10 (16) */ bipush,
    /* 0x11 (17) */ NULL,
    /* 0x12 (18) */ NULL,
    /* 0x13 (19) */ NULL,
    /* 0x14 (20) */ NULL,
    /* 0x15 (21) */ iload,
    /* 0x16 (22) */ lload,
    /* 0x17 (23) */ fload,
    /* 0x18 (24) */ dload,
    /* 0x19 (25) */ aload,
    /* 0x1a (26) */ iload_0,
    /* 0x1b (27) */ iload_1,
    /* 0x1c (28) */ iload_2,
    /* 0x1d (29) */ iload_3,
    /* 0x1e (30) */ lload_0,
    /* 0x1f (31) */ lload_1,
    /* 0x20 (32) */ lload_2,
    /* 0x21 (33) */ lload_3,
    /* 0x22 (34) */ fload_0,
    /* 0x23 (35) */ fload_1,
    /* 0x24 (36) */ fload_2,
    /* 0x25 (37) */ fload_3,
    /* 0x26 (38) */ dload_0,
    /* 0x27 (39) */ dload_1,
    /* 0x28 (40) */ dload_2,
    /* 0x29 (41) */ dload_3,
    /* 0x2a (42) */ aload_0,
    /* 0x2b (43) */ aload_1,
    /* 0x2c (44) */ aload_2,
    /* 0x2d (45) */ aload_3,
    /* 0x2e (46) */ NULL,
    /* 0x2f (47) */ NULL,
    /* 0x30 (48) */ NULL,
    /* 0x31 (49) */ NULL,
    /* 0x32 (50) */ NULL,
    /* 0x33 (51) */ NULL,
    /* 0x34 (52) */ NULL,
    /* 0x35 (53) */ NULL,
    /* 0x36 (54) */ NULL,
    /* 0x37 (55) */ NULL,
    /* 0x38 (56) */ NULL,
    /* 0x39 (57) */ NULL,
    /* 0x3a (58) */ NULL,
    /* 0x3b (59) */ NULL,
    /* 0x3c (60) */ NULL,
    /* 0x3d (61) */ NULL,
    /* 0x3e (62) */ NULL,
    /* 0x3f (63) */ NULL,
    /* 0x40 (64) */ NULL,
    /* 0x41 (65) */ NULL,
    /* 0x42 (66) */ NULL,
    /* 0x43 (67) */ NULL,
    /* 0x44 (68) */ NULL,
    /* 0x45 (69) */ NULL,
    /* 0x46 (70) */ NULL,
    /* 0x47 (71) */ NULL,
    /* 0x48 (72) */ NULL,
    /* 0x49 (73) */ NULL,
    /* 0x4a (74) */ NULL,
    /* 0x4b (75) */ NULL,
    /* 0x4c (76) */ NULL,
    /* 0x4d (77) */ NULL,
    /* 0x4e (78) */ NULL,
    /* 0x4f (79) */ NULL,
    /* 0x50 (80) */ NULL,
    /* 0x51 (81) */ NULL,
    /* 0x52 (82) */ NULL,
    /* 0x53 (83) */ NULL,
    /* 0x54 (84) */ NULL,
    /* 0x55 (85) */ NULL,
    /* 0x56 (86) */ NULL,
    /* 0x57 (87) */ pop_op,
    /* 0x58 (88) */ NULL,
    /* 0x59 (89) */ NULL,
    /* 0x5a (90) */ NULL,
    /* 0x5b (91) */ NULL,
    /* 0x5c (92) */ NULL,
    /* 0x5d (93) */ NULL,
    /* 0x5e (94) */ NULL,
    /* 0x5f (95) */ NULL,
    /* 0x60 (96) */ iadd,
    /* 0x61 (97) */ ladd,
    /* 0x62 (98) */ fadd,
    /* 0x63 (99) */ dadd,
    /* 0x64 (100) */ NULL,
    /* 0x65 (101) */ NULL,
    /* 0x66 (102) */ NULL,
    /* 0x67 (103) */ NULL,
    /* 0x68 (104) */ imul,
    /* 0x69 (105) */ lmul,
    /* 0x6a (106) */ fmul,
    /* 0x6b (107) */ dmul,
    /* 0x6c (108) */ idiv,
    /* 0x6d (109) */ ldiv_handler,
    /* 0x6e (110) */ fdiv,
    /* 0x6f (111) */ ddiv,
    /* 0x70 (112) */ irem,
    /* 0x71 (113) */ lrem,
    /* 0x72 (114) */ frem,
    /* 0x73 (115) */ drem_handler,
    /* 0x74 (116) */ ineg,
    /* 0x75 (117) */ lneg,
    /* 0x76 (118) */ fneg,
    /* 0x77 (119) */ dneg,
    /* 0x78 (120) */ NULL,
    /* 0x79 (121) */ NULL,
    /* 0x7a (122) */ NULL,
    /* 0x7b (123) */ NULL,
    /* 0x7c (124) */ NULL,
    /* 0x7d (125) */ NULL,
    /* 0x7e (126) */ iand,
    /* 0x7f (127) */ land,
    /* 0x80 (128) */ NULL,
    /* 0x81 (129) */ NULL,
    /* 0x82 (130) */ ixor,
    /* 0x83 (131) */ lxor,
    /* 0x84 (132) */ NULL,
    /* 0x85 (133) */ NULL,
    /* 0x86 (134) */ NULL,
    /* 0x87 (135) */ NULL,
    /* 0x88 (136) */ NULL,
    /* 0x89 (137) */ NULL,
    /* 0x8a (138) */ NULL,
    /* 0x8b (139) */ NULL,
    /* 0x8c (140) */ NULL,
    /* 0x8d (141) */ NULL,
    /* 0x8e (142) */ NULL,
    /* 0x8f (143) */ NULL,
    /* 0x90 (144) */ NULL,
    /* 0x91 (145) */ NULL,
    /* 0x92 (146) */ NULL,
    /* 0x93 (147) */ NULL,
    /* 0x94 (148) */ NULL,
    /* 0x95 (149) */ NULL,
    /* 0x96 (150) */ NULL,
    /* 0x97 (151) */ NULL,
    /* 0x98 (152) */ NULL,
    /* 0x99 (153) */ NULL,
    /* 0x9a (154) */ NULL,
    /* 0x9b (155) */ NULL,
    /* 0x9c (156) */ NULL,
    /* 0x9d (157) */ NULL,
    /* 0x9e (158) */ NULL,
    /* 0x9f (159) */ NULL,
    /* 0xa0 (160) */ NULL,
    /* 0xa1 (161) */ NULL,
    /* 0xa2 (162) */ NULL,
    /* 0xa3 (163) */ NULL,
    /* 0xa4 (164) */ NULL,
    /* 0xa5 (165) */ NULL,
    /* 0xa6 (166) */ NULL,
    /* 0xa7 (167) */ NULL,
    /* 0xa8 (168) */ NULL,
    /* 0xa9 (169) */ NULL,
    /* 0xaa (170) */ NULL,
    /* 0xab (171) */ NULL,
    /* 0xac (172) */ ireturn,
    /* 0xad (173) */ NULL,
    /* 0xae (174) */ NULL,
    /* 0xaf (175) */ NULL,
    /* 0xb0 (176) */ NULL,
    /* 0xb1 (177) */ NULL,
    /* 0xb2 (178) */ NULL,
    /* 0xb3 (179) */ NULL,
    /* 0xb4 (180) */ NULL,
    /* 0xb5 (181) */ NULL,
    /* 0xb6 (182) */ NULL,
    /* 0xb7 (183) */ NULL,
    /* 0xb8 (184) */ invokestatic,
    /* 0xb9 (185) */ NULL,
    /* 0xba (186) */ NULL,
    /* 0xbb (187) */ NULL,
    /* 0xbc (188) */ NULL,
    /* 0xbd (189) */ NULL,
    /* 0xbe (190) */ NULL,
    /* 0xbf (191) */ NULL,
    /* 0xc0 (192) */ NULL,
    /* 0xc1 (193) */ NULL,
    /* 0xc2 (194) */ NULL,
    /* 0xc3 (195) */ NULL,
    /* 0xc4 (196) */ NULL,
    /* 0xc5 (197) */ NULL,
    /* 0xc6 (198) */ NULL,
    /* 0xc7 (199) */ NULL,
    /* 0xc8 (200) */ NULL,
    /* 0xc9 (201) */ NULL,
    [0xca ... 0xff] = NULL,
};

#endif // HANDLERS_H
