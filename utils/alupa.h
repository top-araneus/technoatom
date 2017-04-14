//-----------------------------------
//! @file alupa.h
//! ALU Parameters for Assembler
//!
//! team araneus, 2017
//-----------------------------------
#ifndef ALUPA_H
#define ALUPA_H


static const int CODE_DEFAULT_SIZE = 1000; // default number of code strings
static const int REGS_DEFAULT_SIZE = 16; // default number of registers
static const int STEP = 50; // step for enlarging arrays

typedef int BlockType;

static const BlockType EXC = 0;      // forbidden instruction, raise exception if code was wrong interpreted
static const BlockType PUSH_RG = 1;  // push from register to stack
static const BlockType PUSH_VL = 2;  // push value to stack
static const BlockType POP = 3;      //pop from stack to register

static const BlockType JMP = 10;  //jump to label or command
static const BlockType CALL = 11; //jump and save next instruction number to callstack
static const BlockType RET = 12;  //return to instruction from callstack
static const BlockType JE = 13;   //jump if two values from stack were equal
static const BlockType JNE = 14;  //jump if not equal
static const BlockType JL = 15;   //jump if first < last
static const BlockType JLE = 16;  //jump if first <= last
static const BlockType JG = 17;   //jump if first > last
static const BlockType JGE = 18;  //jump if first >= last

static const BlockType ADD = 20;  //addition of two popped values, push result
static const BlockType SUB = 21;  //substraction
static const BlockType MUL = 22;  //multiplication
static const BlockType DIV = 23;  //division

static const BlockType END = 255; //end of program

#endif // ALUPA_H
