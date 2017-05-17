//-----------------------------------
//! @file alu.h
//! Computing module for game AI
//!
//! team araneus, 2017
//-----------------------------------
#ifndef ALU_H
#define ALU_H
#include "math.h"
#include "..\..\stack/stack/stack.h"
#include "..\..\utils\exception.h"
#include "..\..\utils\print.h"
#include "..\..\utils\alupa.h"

/*! @class ALU
 *  @brief arithmetical-logical unit running on bytecode */
class ALU
{
  private:
    Array<BlockType> regs_;  //!< regs_ is an array with registers containing data
    Array<BlockType> code_;  //!< code_ is an array with commands to execute
    Stack<BlockType> stack_; //!< stack_ is a stack containing data ALU operates with
    Stack<BlockType> call_;  //!< call_ is a callstack for recursion

    /*! @fn Load(std::string filename)
     *  @brief Loads bytecode from file to code_ array.
     *  @arg filename is a file from bin_code folder to execute */
    void Load(std::string  filename);

  public:
    /*! @fn ALU(std::string filename)
     *  @brief Initialising constructor gets bytecode from file.
     *  @arg filename is a file from bin_code folder to execute */
    ALU(std::string filename);

    ~ALU();

    /*! @fn void Execute()
     *  @brief Executes bytecode */
    void Execute();

    /*! @fn void Execute(BlockType value, Args... args)
     *  @brief Executes bytecode, pre-pushing values from args into stack */
    template <typename... Args>
    void Execute(BlockType value, Args... args);

    /*! @fn BlockType GetRegister(int reg)
     *  @brief Returns value from register reg
     *  @arg int reg is a number of a register
     *  @return value register keeps */
    BlockType GetRegister(int reg);

    /*! @fn void GetRegister(bool all)
     *  @brief Prints all regs_ array into console if all = true */
    void GetRegister(bool all);

    /*! @fn void GetRegister(int reg, BlockType value)
     *  @brief Presets value of register reg on defined value */
    void SetRegister(int reg, BlockType value);
};

ALU::ALU(std::string filename)
{
  regs_.Resize(kRegsDefaultSize);
  code_.Resize(kCodeDefaultSize);
  Load("..\\..\\bin_code\\" + filename);
}

ALU::~ALU(){}

void ALU::Load(std::string filename)
{
  std::ifstream fin(filename, std::ios_base::in | std::ios_base::binary);
  if (!fin.is_open())
	throw EFileCreationError(__FL__);
  BlockType buff;
  int cnt = 0;
  while (fin.read((char*)&buff, sizeof(buff)))
  {
    code_[cnt++] = buff;
    if (code_.Size() - cnt == 0)
	{
		code_.Resize(code_.Size() + kStep);
	}
  }
  fin.close();
}

void ALU::Execute()
{
  #define CMD(name, num, code)\
	else if(code_[pos] == num)\
	    code\

  int pos = 0;
  while (code_[pos] != kEnd)
  {
	  if(0){}
      #include "alucommands.h"
  }
  #undef CMD(name, num, code)
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
