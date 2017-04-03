#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <fstream>
#include <iostream>
#include <sstream>
#include "..\..\Array.h"

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

void Arithmetics(int code, std::ostream& fout)
{
    cout << "Arithmetics: " << code << endl;
    int buff = code;
    fout.write((char*)&buff, sizeof(buff));
}

void Push_Pop(std::string& current_cmd, int code, std::ostream& fout, bool isReg)
{
    cout << "Push_Pop: " << code << " " << current_cmd << endl;
    int buff = code;
    fout.write((char*)&buff, sizeof(buff));
    if(isReg)
        current_cmd.erase(0,1);
    buff = fromString<int>(current_cmd);
    fout.write((char*)&buff, sizeof(buff));
}

void Jmp_Call(std::string& current_cmd, int code, std::ostream& fout, Array<int>& marks)
{
    int buff = code;
    fout.write((char*)&buff, sizeof(buff));
    current_cmd.erase(0,1);
    buff = marks[fromString<int>(current_cmd)];
    cout << "Jmp_Call: " << code << " " << marks[fromString<int>(current_cmd)] << endl;
    fout.write((char*)&buff, sizeof(buff));
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
    std::string current_cmd;
    int line_number = 0;
    while(!fin.eof())
    {
        fin >> current_cmd;

        if (current_cmd[0] == 'c' || current_cmd[0] == 'j')
        {
            fin >> current_cmd;
            ++line_number;
        }
        else if (current_cmd[0] == ':')
        {
            cout << current_cmd;
            current_cmd.erase(0,1);
            marks[fromString<int>(current_cmd)] = line_number;
            cout << " " << line_number << endl;
            continue;
        }
        ++line_number;
    }
    fin.clear();
    fin.seekg(0, std::ios_base::beg);
    while(!fin.eof())
    {
        fin >> current_cmd;

        /* may crash without if-else */

        if(current_cmd == "push")
        {
            fin >> current_cmd;
            if(current_cmd[0] == 'x')
            {
                Push_Pop(current_cmd, PUSH_RG, fout, true);
            }
            else
            {
                Push_Pop(current_cmd, PUSH_VL, fout, false);
            }
        }
        if(current_cmd == "pop")
        {
            fin >> current_cmd;
            if(current_cmd[0] != 'x')
            {
                std::cout << "Invalid pop argument";
                break;
            }
            else
            {
                Push_Pop(current_cmd, POP, fout, true);
            }

        }
        if(current_cmd == "add")
        {
            Arithmetics(ADD, fout);
        }
        if(current_cmd == "sub")
        {
            Arithmetics(SUB, fout);
        }
        if(current_cmd == "mul")
        {
            Arithmetics(MUL, fout);
        }
        if(current_cmd == "div")
        {
            Arithmetics(DIV, fout);
        }
        if(current_cmd == "jmp")
        {
            fin >> current_cmd;
            Jmp_Call(current_cmd, JMP, fout, marks);
        }
        if(current_cmd == "call")
        {
            fin >> current_cmd;
            Jmp_Call(current_cmd, CALL, fout, marks);
        }
        if(current_cmd == "je")
        {
            fin >> current_cmd;
            Jmp_Call(current_cmd, JE, fout, marks);
        }
        if(current_cmd == "jne")
        {
            fin >> current_cmd;
            Jmp_Call(current_cmd, JNE, fout, marks);
        }
        if(current_cmd == "jl")
        {
            fin >> current_cmd;
            Jmp_Call(current_cmd, JL, fout, marks);
        }
        if(current_cmd == "jle")
        {
            fin >> current_cmd;
            Jmp_Call(current_cmd, JLE, fout, marks);
        }
        if(current_cmd == "jg")
        {
            fin >> current_cmd;
            Jmp_Call(current_cmd, JG, fout, marks);
        }
        if(current_cmd == "jge")
        {
            fin >> current_cmd;
            Jmp_Call(current_cmd, JGE, fout, marks);
        }
        if(current_cmd == "ret")
        {
            int buff = RET;
            fout.write((char*)&buff, sizeof(buff));
            cout << "Ret: " << RET << endl;
        }
        if(current_cmd == "end")
        {
            cout << "End: " << END << endl;
            int buff = END;
            fout.write((char*)&buff, sizeof(buff));
        }
    }
    fin.close();
    fout.close();
}


void Disassembler(const char* input, const char* output)
{
    std::ifstream fin(input, std::ios_base::in | std::ios_base::binary);
    std::ofstream fout(output, std::ios_base::out);
    int buff;
    int cnt = 0;
    while (fin.read((char*)&buff, sizeof(buff)))
    {
        //fin.read((char*)&buff, sizeof(buff));
        switch(buff)
        {
            case EXC:
                throw EALUBadInstruction(__FL__);
            break;

            case PUSH_RG:
                fout << "push x";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case PUSH_VL:
                fout << "push ";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case POP:
                fout << "pop x";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case ADD:
                fout << "add" << endl;
            break;

            case SUB:
            {
                fout << "sub" << endl;
            }
            break;

            case MUL:
                fout << "mul" << endl;
            break;

            case DIV:
            {
                fout << "div" << endl;
            }
            break;

            case JMP:
                fout << "jmp ";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case CALL:
                fout << "call ";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case RET:
                fout << "ret" << endl;
            break;

            case JE:
                fout << "je ";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case JNE:
                fout << "jne ";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case JL:
                fout << "jl ";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case JLE:
                fout << "jle ";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case JG:
                fout << "jg ";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case JGE:
                fout << "jge ";
                fin.read((char*)&buff, sizeof(buff));
                fout << buff << endl;
            break;

            case END:
            {
                fout << "end" << endl;
            }
            break;

        }
    }
    fout.close();
    fin.close();
}

#endif // TRANSLATOR_H
