#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <fstream>
#include <iostream>
#include <sstream>
#include "D:\projects\technoatom\Array.h"

         const int EXC = 0;
         const int PUSH_RG = 1;
         const int PUSH_VL = 2;
         const int POP = 3;

         const int JMP = 10;
         const int CALL = 11;
         const int RET = 12;
         const int JE = 13;
         const int JNE = 14;
         const int JL = 15;
         const int JLE = 16;
         const int JG = 17;
         const int JGE = 18;

         const int ADD = 20;
         const int SUB = 21;
         const int MUL = 22;
         const int DIV = 23;

         const int END = 255;

template<typename T>
T fromString(const std::string& s)
{
    std::istringstream iss(s);
    T res;
    iss >> res;
    return res;
}

const int default_size = 200;
const int default_value = -1;

void Translator(const char* input, const char* output)
{
    Array<int> marks(default_size);
    for (int i = 0; i < default_size; ++i)
    {
        marks[i] = default_value;
    }
    std::ifstream fin(input, std::ios_base::in);
    std::ofstream fout(output, std::ios_base::out | std::ios_base::binary);
    std::string tmp;
    int line_number = 0;
    while(!fin.eof())
    {
        fin >> tmp;
        if (tmp[0] != 'c' && tmp[0] != 'j')
        {
            fin >> tmp;
            if (tmp[0] == ':')
            {
                tmp.erase(0,1);
                marks[fromString<int>(tmp)] = line_number;
            }
        }
        ++line_number;
    }
    fin.clear();
    fin.seekg(0, std::ios_base::beg);
     while(!fin.eof())
     {
         /* static const int EXC = 0;
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
*/
         fin >> tmp;
        if(tmp == "push")
        {
            fin >> tmp;
            if(tmp[0] == 'x')
            {
                int buff = PUSH_RG;
                fout.write((char*)&buff, sizeof(buff));
                tmp.erase(0,1);
                buff = fromString<int>(tmp);
                fout.write((char*)&buff, sizeof(buff));

            }
            else
            {
                int buff = PUSH_VL;
                fout.write((char*)&buff, sizeof(buff));
                buff = fromString<int>(tmp);
                fout.write((char*)&buff, sizeof(buff));
            }
        }
        if(tmp == "pop")
        {
            fin >> tmp;
            if(tmp[0] != 'x')
            {
                std::cout << "Invalid pop argument";
                break;
            }
            else
            {
                int buff = POP;
                fout.write((char*)&buff, sizeof(buff));
                tmp.erase(0,1);
                buff = fromString<int>(tmp);
                fout.write((char*)&buff, sizeof(buff));
            }

        }
        if(tmp = "add")
        {
            int buff = ADD;
            fout.write((char*)&buff, sizeof(buff));
        }
        if(tmp = "sub")
        {
            int buff = SUB;
            fout.write((char*)&buff, sizeof(buff));
        }
        if(tmp = "mul")
        {
            int buff = MUL;
            fout.write((char*)&buff, sizeof(buff));
        }
        if(tmp = "div")
        {
            int buff = DIV;
            fout.write((char*)&buff, sizeof(buff));
        }

     }
}

#endif // TRANSLATOR_H
