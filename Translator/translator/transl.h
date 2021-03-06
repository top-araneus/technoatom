#ifndef TRANSL_H
#define TRANSL_H

#include "commandfactory.h"
#include "fstream"
#include "iostream"
#include "sstream"
#include "workwithfiles.h"
#include "../../../technoatom/stack/stack/array.h"
#include <cstdio>
#include <map>

class Translator
{
public:
  inline Translator(string& in, string& out);
  void CollectIncludes(ifstream& input, Array<string>& list_of_includes_);
  void FirstPass();
  void CollectMarks();
  void SecondPass();
  void ThirdPass();
  ~Translator();
private:
  typename Command::TypeOfMarksMap marks_;
  CommandFactory factory_;
  std::ifstream file_input_;
  std::ifstream file_full_instruction_input_;
  std::ofstream file_full_instruction_output_;
  std::ofstream file_out_;
  Array<string> list_of_includes_;
  bool IsMark(string word);
  bool IsInclude(string word);
};

Translator::Translator(string& in, string& out)
{
  factory_.FillCommands();
  file_input_.open(in.c_str());
  //file_full_instruction_.open("..\\..\\tmp_files\\__tmp_full_instruction_.txt");
  file_out_.open(out.c_str(), ios_base::binary);
  list_of_includes_.PushBack(in);
}

inline bool Translator::IsMark(string word)
{
  return (word[0] == ':');
}

inline bool Translator::IsInclude(string word)
{
  return (word == string("include"));
}

void Translator::CollectIncludes(ifstream& fin, Array<string>& list_of_includes)
{
  string word;
  fin.seekg(0,ios_base::beg);
  while (fin)
  {
    fin >> word;
    if (IsInclude(word))
    {
      fin >> word;
      list_of_includes.PushBack(word);
      ifstream next_input(word.c_str());
      CollectIncludes(next_input, list_of_includes);
    }
  }
}

void Translator::FirstPass( )
{
  print("massive:\n /#\n", list_of_includes_);
  CollectIncludes(file_input_, list_of_includes_);
  print("massive:\n /#\n", list_of_includes_);
  print("..\\..\\tmp_files\\__tmp_full_instruction_.txt");
  file_full_instruction_output_.open("..\\..\\tmp_files\\__tmp_full_instruction_.txt", std::ios_base::app);
  if (file_full_instruction_output_)
  {
    std::ifstream tmp;
    for (auto it = list_of_includes_.begin(); it != list_of_includes_.end(); ++it)
    {
      print("it: /#\n", (*it).c_str());
      tmp.open((*it).c_str());
      if (tmp)
      {
         AppendFromFileToFile(tmp, file_full_instruction_output_);
      }
      tmp.close();
    }
  }
  file_full_instruction_output_.close();
}

void Translator::CollectMarks()
{
  std::string word;
  double current_num_of_word = 0;
  file_full_instruction_input_.open("..\\..\\tmp_files\\__tmp_full_instruction_.txt");
  int increase_of_line_number = 0;
  while(file_full_instruction_input_)
  {
    file_full_instruction_input_ >> word;
    if (IsInclude(word)){
      file_full_instruction_input_ >> word;
      increase_of_line_number = 0;
    }
    else if (IsMark(word)){
      word.erase(0, 1);
      print("\n_word: /#, _num: /#\n", word, current_num_of_word);
      marks_.insert(std::pair<std::string, double>(word, current_num_of_word));
      increase_of_line_number = 0;
    }
    else{
      Command* cmd = factory_.Create(word, &marks_);
      if (cmd != nullptr)
      {
        cmd->SkipArguments(file_full_instruction_input_);
        increase_of_line_number = cmd->GetNumOfArgs() + 1;
      }
      delete cmd;
    }
    current_num_of_word += increase_of_line_number;
  }
  file_full_instruction_input_.close();
}

void Translator::SecondPass()
{
  CollectMarks();
}

void Translator::ThirdPass()
{
  string word;
  file_full_instruction_input_.open("..\\..\\tmp_files\\__tmp_full_instruction_.txt");
  while(file_full_instruction_input_ >> word)
  {
    if(IsInclude(word))
    {
      file_full_instruction_input_ >> word;
    }
    else if(!IsMark(word))
    {
      Command* cmd = factory_.Create(word, &marks_);
      if (cmd != nullptr)
        cmd->ConvertToBin(file_full_instruction_input_, file_out_);
      delete cmd;
    }
  }
  file_full_instruction_input_.close();
}


Translator::~Translator()
{
  file_input_.close();
  file_out_.close();
  remove("..\\..\\tmp_files\\__tmp_full_instruction_.txt");
}


#endif // TRANSL_H
