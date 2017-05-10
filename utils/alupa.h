//-----------------------------------
//! @file alupa.h
//! ALU Parameters for Assembler
//!
//! team araneus, 2017
//-----------------------------------
#ifndef ALUPA_H
#define ALUPA_H


const int CODE_DEFAULT_SIZE = 1000; // default number of code strings
const int REGS_DEFAULT_SIZE = 16; // default number of registers
const int STEP = 50; // step for enlarging arrays

typedef int BlockType;

const BlockType EXC = 0;    // forbidden instruction, raise exception if code was wrong interpreted
const BlockType PUSH_RG = 1;  // push from register to stack
const BlockType PUSH_VL = 2;  // push value to stack
const BlockType POP = 3;    //pop from stack to register

const BlockType JMP = 10;  //jump to label or command
const BlockType CALL = 11; //jump and save next instruction number to callstack
const BlockType RET = 12;  //return to instruction from callstack
const BlockType JE = 13;   //jump if two values from stack were equal
const BlockType JNE = 14;  //jump if not equal
const BlockType JL = 15;   //jump if first < last
const BlockType JLE = 16;  //jump if first <= last
const BlockType JG = 17;   //jump if first > last
const BlockType JGE = 18;  //jump if first >= last

const BlockType ADD = 20;  //addition of two popped values, push result
const BlockType SUB = 21;  //substraction
const BlockType MUL = 22;  //multiplication
const BlockType DIV = 23;  //division

const BlockType END = 255; //end of program

#endif // ALUPA_H
