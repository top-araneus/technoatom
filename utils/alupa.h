//-----------------------------------
//! @file alupa.h
//! ALU Parameters for Assembler
//!
//! team araneus, 2017
//-----------------------------------
#ifndef ALUPA_H
#define ALUPA_H


const int kCodeDefaultSize = 1000; // default number of code strings
const int kRegsDefaultSize = 16; // default number of registers
const int kStep = 50; // step for enlarging arrays

typedef double BlockType;

const BlockType kExp = 0;    // forbidden instruction, raise exception if code was wrong interpreted
const BlockType kPushRG = 1;  // push from register to stack
const BlockType kPushVL = 2;  // push value to stack
const BlockType kPop = 3;    //pop from stack to register

const BlockType kJmp = 10;  //jump to label or command
const BlockType kCall = 11; //jump and save next instruction number to callstack
const BlockType kRet = 12;  //return to instruction from callstack
const BlockType kJe = 13;   //jump if two values from stack were equal
const BlockType kJne = 14;  //jump if not equal
const BlockType kJl = 15;   //jump if first < last
const BlockType kJle = 16;  //jump if first <= last
const BlockType kJg = 17;   //jump if first > last
const BlockType kJge = 18;  //jump if first >= last

const BlockType kAdd = 20;  //addition of two popped values, push result
const BlockType kSub = 21;  //substraction
const BlockType kMul = 22;  //multiplication
const BlockType kDiv = 23;  //division
const BlockType kSqrt = 24; //^(1/2)

const BlockType kNorm = 30; // normiration of vector
const BlockType kAbs = 31;  // absolute value of vector

const BlockType kEnd = 255; //end of program

#endif // ALUPA_H
