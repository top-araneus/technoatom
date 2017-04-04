//-----------------------------------
//! @file alupa.h
//! ALU parameters
//!
//! author faradaym, 2017
//-----------------------------------
#ifndef ALUPA_H
#define ALUPA_H


static const int CODE_DEFAULT_SIZE = 1000;
static const int REGS_DEFAULT_SIZE = 16;
static const int STEP = 50;

typedef int BlockType;

static const BlockType EXC = 0;
static const BlockType PUSH_RG = 1;
static const BlockType PUSH_VL = 2;
static const BlockType POP = 3;

static const BlockType JMP = 10;
static const BlockType CALL = 11;
static const BlockType RET = 12;
static const BlockType JE = 13;
static const BlockType JNE = 14;
static const BlockType JL = 15;
static const BlockType JLE = 16;
static const BlockType JG = 17;
static const BlockType JGE = 18;

static const BlockType ADD = 20;
static const BlockType SUB = 21;
static const BlockType MUL = 22;
static const BlockType DIV = 23;

static const BlockType END = 255;

#endif // ALUPA_H
