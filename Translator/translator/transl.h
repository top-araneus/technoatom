#ifndef TRANSL_H
#define TRANSL_H
#include <string>
#include <map>
#include "../../utils/alupa.h"
#include "../../stack/stack/array.h"
#include "typeconvert.h"


class Command
{
  public:
  typedef std::map<std::string, BlockType> CommandMap;
  inline int GetNumOfArgs(){
    return num_of_args_;
  }
  virtual void FillIndexOfCmd(std::ifstream& fin) = 0;
  virtual void FillArguments(std::ifstream& fin)
  {
     for(int i = 0; i < num_of_args_; i++)
     {
       std::string word;
       fin >> word;
       arguments_.PushBack(fromString<BlockType>(word));
     }
  }
  inline void WriteToFile(std::ofstream& fout)
  {
    fout.write((char*)&index_of_cmd_, sizeof(index_of_cmd_));
    for(auto it = arguments_.begin(); it != arguments_.end(); ++it)
    {
      fout.write((char*)&(*it), sizeof(*it));
    }
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout)
  {
    FillIndexOfCmd(fin);
    FillArguments(fin);
    WriteToFile(fout);
  }
  virtual ~Command() = 0;
  protected:
  int num_of_args_ = 0;
  BlockType index_of_cmd_;
  Array<BlockType> arguments_;
  CommandMap* marks_;
};

class PushCmd : public Command
{
  private:
  inline bool IsRegisterArg(std::string& word)
  {
    return (word[0] == 'x');
  }
  public:
  inline PushCmd()
  {
    num_of_args_ = 1;
  }
  virtual void FillIndexOfCmd(std::ifstream& fin) override
  {
    int initial_pos_in_file = fin.tellg();
    std::string word;
    fin >> word;
    if(IsRegisterArg(word)){
    word.erase(0, 1);
    index_of_cmd_ = kPushRG;
    }
    else{
    index_of_cmd_ = kPushVL;
    }
    fin.seekg(initial_pos_in_file);
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class PopCmd : public Command
{
  inline PopCmd()
  {
    num_of_args_ = 1;
    index_of_cmd_ = kPop;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    std::string word;
    fin >> word;
    word.erase(0, 1);
    arguments_.PushBack(fromString<BlockType>(word));
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class JmpCmd : public Command
{
protected:
  inline bool IsMark(std::string word)
  {
    return (word[0] == '>');
  }
public:
  inline JmpCmd(){}
  inline JmpCmd(CommandMap& marks)
  {
    marks_ = &marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJmp;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    std::string word;
    fin >> word;
    if(IsMark(word)){
      word.erase(0, 1);
      auto number_of_line = marks_->find(word);
      if (number_of_line != marks_->end()){
        arguments_.PushBack(number_of_line->second);
      }
      else{
        print("Mark: /# did not found",word);
      }
    }
    else{
      arguments_.PushBack(fromString<BlockType>(word));
    }
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout)
  {
    Command::ConvertToBin(fin, fout);
  }
};

class CallCmd : public JmpCmd
{
  inline CallCmd(CommandMap& marks)
  {
    marks_ = &marks;
    num_of_args_ = 1;
    index_of_cmd_ = kCall;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class RetCmd : public Command
{
  inline RetCmd()
  {
    num_of_args_ = 0;
    index_of_cmd_ = kRet;
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class JeCmd : public JmpCmd
{
  inline JeCmd(CommandMap marks)
  {
    marks_ = &marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJe;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class JneCmd : public JmpCmd
{
  inline JneCmd(CommandMap marks)
  {
    marks_ = &marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJne;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class JlCmd : public JmpCmd
{
  inline JlCmd(CommandMap marks)
  {
    marks_ = &marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJl;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class JleCmd : public JmpCmd
{
  inline JleCmd(CommandMap marks)
  {
    marks_ = &marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJle;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class JgCmd : public JmpCmd
{
  inline JgCmd(CommandMap marks)
  {
    marks_ = &marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJg;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class JgeCmd : public JmpCmd
{
  inline JgeCmd(CommandMap marks)
  {
    marks_ = &marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJge;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class AddCmd : public Command
{
  inline AddCmd()
  {
    num_of_args_ = 0;
    index_of_cmd_ = kAdd;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class SubCmd : public Command
{
  inline SubCmd()
  {
    num_of_args_ = 0;
    index_of_cmd_ = kSub;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class MulCmd : public Command
{
  inline MulCmd()
  {
    num_of_args_ = 0;
    index_of_cmd_ = kMul;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class DivCmd : public Command
{
  inline DivCmd()
  {
    num_of_args_ = 0;
    index_of_cmd_ = kDiv;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class SqrtCmd : public Command
{
  inline SqrtCmd()
  {
    num_of_args_ = 0;
    index_of_cmd_ = kSqrt;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class NormCmd : public Command
{
  inline NormCmd()
  {
    num_of_args_ = 4;
    index_of_cmd_ = kNorm;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class AbsCmd : public Command
{
  inline AbsCmd()
  {
    num_of_args_ = 2;
    index_of_cmd_ = kAbs;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

class EndCmd : public Command
{
  inline EndCmd()
  {
    num_of_args_ = 0;
    index_of_cmd_ = kEnd;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
  virtual void ConvertToBin(std::ifstream& fin, std::ofstream& fout) override
  {
    Command::ConvertToBin(fin, fout);
  }
};

#endif // TRANSL_H
