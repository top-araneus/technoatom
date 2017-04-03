//-----------------------------------
//! @file alu.h
//! Computing module for game AI
//!
//! team araneus, 2017
//-----------------------------------
#ifndef ALU_H
#define ALU_H
#include "array.h"
#include "stack.h"
#include "exception.h"
#include "print.h"

class ALU
{
    private:

        static const int EXC = 0;
        static const int PUSH_RG = 1;
        static const int PUSH_VL = 2;
        static const int POP = 3;

        static const int JMP = 10;
        static const int CALL = 11;
        static const int RET = 12;
        static const int JE = 13;
        static const int JNE = 14;
        static const int JL = 15;
        static const int JLE = 16;
        static const int JG = 17;
        static const int JGE = 18;

        static const int ADD = 20;
        static const int SUB = 21;
        static const int MUL = 22;
        static const int DIV = 23;

        static const int END = 255;

        Array<int> _regs;
        Array<int> _code;
        Stack<int> _stack;
        Stack<int> _call;
        void Load(const char* filename);
    public:
        ALU();
        ~ALU();
        void Execute();
};

ALU::ALU()
{
    print("Hi!");
    _regs.Resize(256);
    _code.Resize(1000);
    Load("code.bin");
    Execute();
}

ALU::~ALU()
{
    print("Bye!");
}

void ALU::Load(const char* filename)
{
    std::ifstream fin(filename, std::ios_base::in | std::ios_base::binary);
    int buff;
    int cnt = 0;
    while (!fin.eof())
    {
        fin.read((char*)&buff, sizeof(buff));
        _code[cnt++] = buff;
    }
    fin.close();

    /*! @brief 2+2 = 4 */
   /* _code[0] = PUSH_VL;
    _code[1] = 2;
    _code[2] = PUSH_VL;
    _code[3] = 2;
    _code[4] = ADD;
    _code[5] = POP;
    _code[6] = 0;
    _code[7] = END;*/
/*
       _code[0] = PUSH_VL;
       _code[1] = 1;
       _code[2] = PUSH_VL;
       _code[3] = 5;
       _code[4] = CALL;
       _code[5] = 6+2;
       _code[6] = JMP;
       _code[7] = 21+2;
       _code[8] = POP;
       _code[9] = 0;
       _code[10] = PUSH_RG;
       _code[9+2] = 0;
       _code[10+2] = PUSH_RG;
       _code[11+2] = 0;
       _code[12+2] = PUSH_VL;
       _code[13+2] = 1;
       _code[14+2] = JE;
       _code[15+2] = 19+2;

       _code[16+2] = SUB;
       _code[17+2] = CALL;
       _code[18+2]  = 6;
       _code[19+2] = MUL;
       _code[20+2] = RET;
       _code[23] = POP;
       _code[24] = 0;
       _code[25] = END;*/
    /*! @brief (5+9)/2 = 7 */
/*    _regs[1] = 5;
    _regs[2] = 9;

    _code[0] = PUSH_RG;
    _code[1] = 1;
    _code[2] = PUSH_RG;
    _code[3] = 2;
    _code[4] = ADD;
    _code[5] = PUSH_VL;
    _code[6] = 2;
    _code[7] = DIV;
    _code[8] = POP;
    _code[9] = 0;
    _code[10] = END;*/

    /*! @brief 1 and 3 in stack, skip 2 */
/*    _code[0] = PUSH_VL;
    _code[1] = 1;
    _code[2] = JMP;
    _code[3] = 6;
    _code[4] = PUSH_VL;
    _code[5] = 2;
    _code[6] = PUSH_VL;
    _code[7] = 3;
    _code[8] = POP;
    _code[9] = 0;
    _code[10] = POP;
    _code[11] = 0;
    _code[12] = END;*/
}

void ALU::Execute()
{
    int pos = 0;
    while (_code[pos] != END)
    {
        switch(_code[pos])
        {
            case EXC:
                throw EALUBadInstruction(__FL__);
            break;

            case PUSH_RG:
                _stack.push(_regs[_code[++pos]]);
                ++pos;
            break;

            case PUSH_VL:
                _stack.push(_code[++pos]);
                ++pos;
            break;

            case POP:
                _regs[_code[++pos]] = _stack.pop();
                ++pos;
            break;

            case ADD:
                _stack.push(_stack.pop() + _stack.pop());
                ++pos;
            break;

            case SUB:
            {
                int subtr = _stack.pop();
                _stack.push(_stack.pop() - subtr);
                ++pos;
            }
            break;

            case MUL:
                _stack.push(_stack.pop() * _stack.pop());
                ++pos;
            break;

            case DIV:
            {
                int dividend = _stack.pop();
                _stack.push(_stack.pop() / dividend);
                ++pos;
            }
            break;

            case JMP:
                pos = _code[pos+1];
            break;

            case CALL:
                _call.push(pos+1);
                pos = _code[pos+1];
            break;

            case RET:
                pos = _call.pop();
            break;

            case JE:
                if (_stack.pop() == _stack.pop())
                    pos = _code[pos+1];
                else
                    pos += 2;
            break;

            case JNE:
                if (_stack.pop() != _stack.pop())
                    pos = _code[pos+1];
                else
                    pos += 2;
            break;

            case JL:
                if (_stack.pop() > _stack.pop())
                    pos = _code[pos+1];
                else
                    pos += 2;
            break;

            case JLE:
                if (_stack.pop() >= _stack.pop())
                    pos = _code[pos+1];
                else
                    pos += 2;
            break;

            case JG:
                if (_stack.pop() < _stack.pop())
                    pos = _code[pos+1];
                else
                    pos += 2;
            break;

            case JGE:
                if (_stack.pop() <= _stack.pop())
                    pos = _code[pos+1];
                else
                    pos += 2;
            break;

            case END:
                print("/#", _regs[0]);
            break;

        }
    }
    print("In 0 register: /#\n", _regs[0]);
}

#endif // ALU_H
