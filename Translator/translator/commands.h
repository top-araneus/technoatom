#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <map>
#include "../../utils/alupa.h"
#include "../../stack/stack/array.h"
#include "typeconvert.h"

class Command
{
  public:
  typedef std::map<std::string, BlockType> TypeOfMarksMap;
  inline int GetNumOfArgs(){
    return num_of_args_;
  }
  virtual void FillIndexOfCmd(std::ifstream& fin){}
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
  void ConvertToBin(std::ifstream& fin, std::ofstream& fout)
  {
    this->FillIndexOfCmd(fin);
    this->FillArguments(fin);
    this->WriteToFile(fout);
  }
  void SkipArguments(std::ifstream& fin)
  {
    string word;
    for(int i = 0; i < num_of_args_; ++i)
    {
      fin >> word;
    }
  }
  virtual ~Command(){}
  protected:
  int num_of_args_ = 0;
  BlockType index_of_cmd_ = 0;
  Array<BlockType> arguments_;
  TypeOfMarksMap* marks_ = nullptr;
};

class PushCmd : public Command
{
  private:
  inline bool IsRegisterArg(std::string& word)
  {
    return (word[0] == 'x');
  }
  public:
  inline PushCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 1;
  }
  virtual void FillIndexOfCmd(std::ifstream& fin) override
  {
    std::string word;
    fin >> word;
    if(IsRegisterArg(word)){
      word.erase(0, 1);
      index_of_cmd_ = kPushRG;
    }
    else{
      index_of_cmd_ = kPushVL;
    }
    arguments_.PushBack(fromString<BlockType>(word));
  }
  virtual void FillArguments(std::ifstream& fin) override{}
};

class PopCmd : public Command
{
public:
  inline PopCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
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
  inline JmpCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
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
      print("\n__Some JMP command. _word: /#, _line: /#\n", word, number_of_line->second);
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
};

class CallCmd : public JmpCmd
{
public:
  inline CallCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 1;
    index_of_cmd_ = kCall;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
};

class RetCmd : public Command
{
public:
  inline RetCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 0;
    index_of_cmd_ = kRet;
  }
};

class JeCmd : public JmpCmd
{
public:
  inline JeCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJe;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
};

class JneCmd : public JmpCmd
{
public:
  inline JneCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJne;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
};

class JlCmd : public JmpCmd
{
public:
  inline JlCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJl;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
};

class JleCmd : public JmpCmd
{
public:
  inline JleCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJle;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
};

class JgCmd : public JmpCmd
{
public:
  inline JgCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJg;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
};

class JgeCmd : public JmpCmd
{
public:
  inline JgeCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 1;
    index_of_cmd_ = kJge;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    JmpCmd::FillArguments(fin);
  }
};

class AddCmd : public Command
{
public:
  inline AddCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 0;
    index_of_cmd_ = kAdd;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
};

class SubCmd : public Command
{
public:
  inline SubCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 0;
    index_of_cmd_ = kSub;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
};

class MulCmd : public Command
{
public:
  inline MulCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 0;
    index_of_cmd_ = kMul;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
};

class DivCmd : public Command
{
public:
  inline DivCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 0;
    index_of_cmd_ = kDiv;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
};

class SqrtCmd : public Command
{
public:
  inline SqrtCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 0;
    index_of_cmd_ = kSqrt;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
};

class NormCmd : public Command
{
public:
  inline NormCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 4;
    index_of_cmd_ = kNorm;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
};

class AbsCmd : public Command
{
public:
  inline AbsCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 2;
    index_of_cmd_ = kAbs;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
};

class EndCmd : public Command
{
public:
  inline EndCmd(TypeOfMarksMap* marks)
  {
    marks_ = marks;
    num_of_args_ = 0;
    index_of_cmd_ = kEnd;
  }
  virtual void FillArguments(std::ifstream& fin) override
  {
    Command::FillArguments(fin);
  }
};

#endif // COMMANDS_H
