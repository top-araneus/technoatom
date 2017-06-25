#ifndef ALUCOMMANDS_H
#define ALUCOMMANDS_H

#define EXP_CODE {\
throw EALUBadInstruction(__FL__);\
}\

#define PUSH_RG_CODE {\
stack_.push(regs_[code_[++pos]]);\
++pos;\
}\

#define PUSH_VL_CODE {\
stack_.push(code_[++pos]);\
++pos;\
}\

#define POP_CODE {\
regs_[code_[++pos]] = stack_.pop();\
++pos;\
}\

#define ADD_CODE {\
stack_.push(stack_.pop() + stack_.pop());\
++pos;\
}\

#define SUB_CODE {\
BlockType subtr = stack_.pop();\
stack_.push(stack_.pop() - subtr);\
++pos;\
}\

#define MUL_CODE {\
stack_.push(stack_.pop() * stack_.pop());\
++pos;\
}\

#define DIV_CODE {\
BlockType dividend = stack_.pop();\
stack_.push(stack_.pop() / dividend);\
++pos;\
}\

#define JMP_CODE {\
pos = code_[pos+1];\
}\

#define CALL_CODE {\
call_.push(pos+2);\
pos = code_[pos+1];\
}\

#define RET_CODE {\
pos = call_.pop();\
}\

#define JE_CODE {\
if (stack_.pop() == stack_.pop())\
  pos = code_[pos+1];\
else\
  pos += 2;\
}\

#define JNE_CODE {\
if (stack_.pop() != stack_.pop())\
  pos = code_[pos+1];\
else\
  pos += 2;\
}\

#define JL_CODE {\
if (stack_.pop() > stack_.pop())\
  pos = code_[pos+1];\
else\
  pos += 2;\
}\

#define JLE_CODE {\
if (stack_.pop() >= stack_.pop())\
  pos = code_[pos+1];\
else\
  pos += 2;\
}\

#define JG_CODE {\
if (stack_.pop() < stack_.pop())\
  pos = code_[pos+1];\
else\
  pos += 2;\
}\

#define JGE_CODE {\
if (stack_.pop() <= stack_.pop())\
  pos = code_[pos+1];\
else\
  pos += 2;\
}\

#define SQRT_CODE {\
stack_.push(sqrt(stack_.pop()));\
++pos;\
}\

#define NORM_CODE {\
double x0 = stack_.pop();\
double y0 = stack_.pop();\
double x = stack_.pop();\
double y = stack_.pop();\
if (x == x0 && y == y0)\
{\
  print("trying to divide by zero in ALU");\
  stack_.push(0);\
  stack_.push(0);\
}\
else\
{\
  double res_x = (x - x0)/(sqrt((x-x0)*(x-x0) + (y-y0)*(y-y0)));\
  double res_y = (y - y0)/(sqrt((x-x0)*(x-x0) + (y-y0)*(y-y0)));\
  stack_.push(res_y);\
  stack_.push(res_x);\
}\
++pos;\
}\

#define ABS_CODE {\
double x = stack_.pop();\
double y = stack_.pop();\
double abs = sqrt(x*x + y*y);\
stack_.push(abs);\
++pos;\
}\

#define END_CODE {\
	break;\
}\

CMD(EXP, kExp, EXP_CODE)
CMD(PUSH_RG, kPushRG, PUSH_RG_CODE)
CMD(PUSH_VL, kPushVL, PUSH_VL_CODE)
CMD(POP, kPop, POP_CODE)
CMD(ADD, kAdd, ADD_CODE)
CMD(SUB, kSub, SUB_CODE)
CMD(MUL, kMul, MUL_CODE)
CMD(DIV, kDiv, DIV_CODE)
CMD(JMP, kJmp, JMP_CODE)
CMD(CALL, kCall, CALL_CODE)
CMD(RET, kRet, RET_CODE)
CMD(JE, kJe, JE_CODE)
CMD(JNE, kJne, JNE_CODE)
CMD(JL, kJl, JL_CODE)
CMD(JLE, kJle, JLE_CODE)
CMD(JG, kJg, JG_CODE)
CMD(JGE, kJge, JGE_CODE)
CMD(SQRT, kSqrt, SQRT_CODE)
CMD(NORM, kNorm, NORM_CODE)
CMD(ABS, kAbs, ABS_CODE)
CMD(END, kEnd, END_CODE)

#undef EXP_CODE
#undef PUSH_RG_CODE
#undef PUSH_VL_CODE
#undef POP_CODE
#undef ADD_CODE
#undef SUB_CODE
#undef MUL_CODE
#undef DIV_CODE
#undef JMP_CODE
#undef CALL_CODE
#undef RET_CODE
#undef JE_CODE
#undef JNE_CODE
#undef JL_CODE
#undef JLE_CODE
#undef JG_CODE
#undef JGE_CODE
#undef SQRT_CODE
#undef NORM_CODE
#undef ABS_CODE
#undef END_CODE


#endif // ALUCOMMANDS_H
