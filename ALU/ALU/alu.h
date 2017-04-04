//-----------------------------------
//! @file alu.h
//! Computing module for game AI
//!
//! team araneus, 2017
//-----------------------------------
#ifndef ALU_H
#define ALU_H
#include "..\..\stack\array.h"
#include "..\..\stack\stack.h"
#include "..\..\exception.h"
#include "..\..\print.h"

template <typename BlockType = int>
class ALU
{
    private:
        static const int CODE_DEFAULT_SIZE = 1000;
        static const int REGS_DEFAULT_SIZE = 16;
        static const int STEP = 50;

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

        Array<BlockType> regs_;
        Array<BlockType> code_;
        Stack<BlockType> stack_;
        Stack<BlockType> call_;
        void Load(std::string  filename);

    public:
        ALU(std::string filename);
        ~ALU();
        void Execute();
        BlockType GetRegister(int reg);
        void GetRegister(bool all);
        void SetRegister(int reg, BlockType value);
};

template <typename BlockType>
ALU<BlockType>::ALU(std::string filename)
{
    regs_.Resize(REGS_DEFAULT_SIZE);
    code_.Resize(CODE_DEFAULT_SIZE);
    Load("..\\..\\bin_code\\" + filename);
}

template <typename BlockType>
ALU<BlockType>::~ALU()
{
}

template <typename BlockType>
void ALU<BlockType>::Load(std::string filename)
{
    std::ifstream fin(filename, std::ios_base::in | std::ios_base::binary);
    BlockType buff;
    int cnt = 0;
    if (!fin.is_open())
        throw EFileCreationError(__FL__);
    while (fin.read((char*)&buff, sizeof(buff)))
    {
        code_[cnt++] = buff;
        if (code_.Size() - cnt == 0)
            code_.Resize(code_.Size() + STEP);
    }
    fin.close();

}

template <typename BlockType>
void ALU<BlockType>::Execute()
{
    int pos = 0;
    while (code_[pos] != END)
    {
        switch(code_[pos])
        {
            case EXC:
                throw EALUBadInstruction(__FL__);
            break;

            case PUSH_RG:
                stack_.push(regs_[code_[++pos]]);
                ++pos;
            break;

            case PUSH_VL:
                stack_.push(code_[++pos]);
                ++pos;
            break;

            case POP:
                regs_[code_[++pos]] = stack_.pop();
                ++pos;
            break;

            case ADD:
                stack_.push(stack_.pop() + stack_.pop());
                ++pos;
            break;

            case SUB:
            {
                BlockType subtr = stack_.pop();
                stack_.push(stack_.pop() - subtr);
                ++pos;
            }
            break;

            case MUL:
                stack_.push(stack_.pop() * stack_.pop());
                ++pos;
            break;

            case DIV:
            {
                BlockType dividend = stack_.pop();
                stack_.push(stack_.pop() / dividend);
                ++pos;
            }
            break;

            case JMP:
                pos = code_[pos+1];
            break;

            case CALL:
                call_.push(pos+2);
                pos = code_[pos+1];
            break;

            case RET:
                pos = call_.pop();
            break;

            case JE:
                if (stack_.pop() == stack_.pop())
                    pos = code_[pos+1];
                else
                    pos += 2;
            break;

            case JNE:
                if (stack_.pop() != stack_.pop())
                    pos = code_[pos+1];
                else
                    pos += 2;
            break;

            case JL:
                if (stack_.pop() > stack_.pop())
                    pos = code_[pos+1];
                else
                    pos += 2;
            break;

            case JLE:
                if (stack_.pop() >= stack_.pop())
                    pos = code_[pos+1];
                else
                    pos += 2;
            break;

            case JG:
                if (stack_.pop() < stack_.pop())
                    pos = code_[pos+1];
                else
                    pos += 2;
            break;

            case JGE:
                if (stack_.pop() <= stack_.pop())
                    pos = code_[pos+1];
                else
                    pos += 2;
            break;

            case END:
            break;

        }
    }
}

template <typename BlockType>
BlockType ALU<BlockType>::GetRegister(int reg)
{
    return regs_[reg];
}

template <typename BlockType>
void ALU<BlockType>::GetRegister(bool all)
{
    if (all)
    {
        cout << regs_ << endl;
    }
}

template <typename BlockType>
void ALU<BlockType>::SetRegister(int reg, BlockType value)
{
    regs_[reg] = value;
}
#endif // ALU_H
