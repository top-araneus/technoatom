//-----------------------------------
//! @file alu.h
//! Computing module for game AI
//!
//! team araneus, 2017
//-----------------------------------
#ifndef ALU_H
#define ALU_H
#include "..\..\stack/stack/array.h"
#include "..\..\stack/stack/stack.h"
#include "..\..\utils\exception.h"
#include "..\..\utils\print.h"
#include "..\..\utils\alupa.h"

class ALU
{
    private:
        Array<BlockType> regs_;
        Array<BlockType> code_;
        Stack<BlockType> stack_;
        Stack<BlockType> call_;
        void Load(std::string  filename);

    public:
        ALU(std::string filename);
        ~ALU();
        void Execute();
        template <typename... Args>
        void Execute(BlockType value, Args... args);
        BlockType GetRegister(int reg);
        void GetRegister(bool all);
        void SetRegister(int reg, BlockType value);
};

ALU::ALU(std::string filename)
{
    regs_.Resize(REGS_DEFAULT_SIZE);
    code_.Resize(CODE_DEFAULT_SIZE);
    Load("..\\..\\bin_code\\" + filename);
}

ALU::~ALU()
{
}

void ALU::Load(std::string filename)
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

void ALU::Execute()
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

template <typename... Args>
void ALU::Execute(BlockType value, Args... args)
{
    stack_.push(value);
    Execute(args...);
}

BlockType ALU::GetRegister(int reg)
{
    return regs_[reg];
}

void ALU::GetRegister(bool all)
{
    if (all)
    {
        cout << regs_ << endl;
    }
}

void ALU::SetRegister(int reg, BlockType value)
{
    regs_[reg] = value;
}
#endif // ALU_H
