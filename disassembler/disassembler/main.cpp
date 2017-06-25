#include "../../utils/alupa.h"
#include <iostream>
#include <fstream>
using namespace std;


/*! @fn Disassembler(std::string input, std::string output)
 * @brief Gets ALU bytecode from input file and returns assembler code in output file */
void Disassembler(std::string input, std::string output)
{
    std::ifstream fin(input.c_str(), std::ios_base::in | std::ios_base::binary);
  if (!fin.is_open())
  {
    cout << "File didn't open" << endl;
    return;
  }
    std::ofstream fout(output.c_str(), std::ios_base::out);
  BlockType buff;
  long number_of_word = 0;
    while (fin.read((char*)&buff, sizeof(buff)))
    {
        if (buff == kExp)
        {
                cout << "invalid instruction EXC (0) in code" << endl;
        }
        else if (buff == kPushRG)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "push x";
                fin.read((char*)&buff, sizeof(buff));
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << buff << endl;
        }
        else if (buff == kPushVL)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "push ";
                fin.read((char*)&buff, sizeof(buff));
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << buff << endl;
        }
        else if (buff == kPop)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "pop x";
                fin.read((char*)&buff, sizeof(buff));
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << buff << endl;
        }
        else if (buff == kAdd)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "add" << endl;
        }
        else if (buff == kSub)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "sub" << endl;
        }
        else if (buff == kMul)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "mul" << endl;
        }
        else if (buff == kDiv)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "div" << endl;
        }
        else if (buff == kAbs)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "abs" << endl;
        }
        else if (buff == kNorm)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "norm" << endl;
        }
        else if (buff == kSqrt)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "sqrt" << endl;
        }
        else if (buff == kJmp)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "jmp ";
                fin.read((char*)&buff, sizeof(buff));
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << buff << endl;
        }
        else if (buff == kCall)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "call ";
                fin.read((char*)&buff, sizeof(buff));
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << buff << endl;
        }
        else if (buff == kRet)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "ret" << endl;
        }
        else if (buff == kJe)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "je ";
                fin.read((char*)&buff, sizeof(buff));
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << buff << endl;
        }
        else if (buff == kJne)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "jne ";
                fin.read((char*)&buff, sizeof(buff));
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << buff << endl;
        }
        else if (buff == kJl)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "jl ";
                fin.read((char*)&buff, sizeof(buff));
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << buff << endl;
        }
        else if (buff == kJle)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "jle ";
                fin.read((char*)&buff, sizeof(buff));
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << buff << endl;
        }
        else if (buff == kJg)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "jg ";
                fin.read((char*)&buff, sizeof(buff));
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << buff << endl;
        }
        else if (buff == kJge)
        {
            fout << number_of_word << "_#";
            number_of_word += 1;
            fout << "jge ";
            fin.read((char*)&buff, sizeof(buff));
            fout << number_of_word << "_#";
            number_of_word += 1;
            fout << buff << endl;
        }
        else if (buff == kEnd)
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "end" << endl;
        }
        else
        {
                fout << number_of_word << "_#";
                number_of_word += 1;
                fout << "error" << endl;
        }
    }
    fout.close();
    fin.close();
}


int main()
{
    std::string from("pursuit80_old.bin");
    std::string to("disasmed_pursuit_old.alu");
    cout << "started" << endl;
    Disassembler("..\\..\\bin_code\\" + from, "..\\..\\disassembler_code\\" + to);
    cout << "done" << endl;

    return 0;
}
