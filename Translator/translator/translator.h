#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <fstream>
#include <iostream>
#include <sstream>
#include "../../../technoatom/stack/stack/array.h"
#include "../../utils/alupa.h"


const int default_size = 200;
const int default_value = -1;

/*! @fn T fromString(const std::string& s)
    @brief Converts string value to defined type and returns it */
template<typename T>
T fromString(const std::string& s)
{
    std::istringstream iss(s);
    T res;
    iss >> res;
    return res;
}

/*! @fn Arithmetics(int code, std::ostream& fout)
    @brief Generates bytecode for arithmetical operations (add etc.)
    @arg BlockType code is an operation code to write
    @arg fout is a file to write */
void Arithmetics(BlockType code, std::ostream& fout)
{
    cout << "Arithmetics: " << code << endl;
    BlockType buff = code;
    fout.write((char*)&buff, sizeof(buff));
}

/*! @fn Push_Pop(std::string& current_cmd, BlockType code, std::ostream& fout, bool isReg)
    @brief Generates bytecode for push and pop operations
    @arg BlockType code is an operation code to write
    @arg fout is a file to write
    @arg isReg is a marker for push type
    @arg current_cmd is a string with current command to translate
    */
void Push_Pop(std::string& current_cmd, BlockType code, std::ostream& fout, bool isReg)
{
    cout << "Push_Pop: " << code << " " << current_cmd << endl;
    BlockType buff = code;
    fout.write((char*)&buff, sizeof(buff));
    if(isReg)
        current_cmd.erase(0,1);
    buff = fromString<BlockType>(current_cmd);
    fout.write((char*)&buff, sizeof(buff));
}

/*! @fn Jmp_Call(std::string& current_cmd, BlockType code, std::ostream& fout, Array<BlockType>& marks)
    @brief Generates bytecode for jump constructions
    @arg BlockType code is an operation code to write
    @arg fout is a file to write
    @arg marks is an array with labels' addresses
    @arg current_cmd is a string with current command to translate
    */
void Jmp_Call(std::string& current_cmd, BlockType code, std::ostream& fout, Array<BlockType>& marks)
{
    BlockType buff = code;
    fout.write((char*)&buff, sizeof(buff));
    current_cmd.erase(0,1);
    buff = marks[fromString<BlockType>(current_cmd)];
    cout << "Jmp_Call: " << code << " " << marks[fromString<BlockType>(current_cmd)] << endl;
    fout.write((char*)&buff, sizeof(buff));
}

/*! @fn Translator(std::string input, std::string output)
    @brief Translates assembler code from input into ALU bytecode to output */
void Translator(std::string input, std::string output)
{
    Array<BlockType> marks(default_size);
    for (int i = 0; i < default_size; ++i)
    {
        marks[i] = default_value;
    }
    std::ifstream fin(input.c_str(), std::ios_base::in);
    std::ofstream fout(output.c_str(), std::ios_base::out | std::ios_base::binary);
	if (!fin.is_open())
	{
        cout << "File didn't open" << endl;
		return;
	}
    std::string current_cmd;
    BlockType line_number = 0;
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
            marks[fromString<BlockType>(current_cmd)] = line_number;
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
            BlockType buff = RET;
            fout.write((char*)&buff, sizeof(buff));
            cout << "Ret: " << RET << endl;
        }
        if(current_cmd == "end")
        {
            cout << "End: " << END << endl;
            BlockType buff = END;
            fout.write((char*)&buff, sizeof(buff));
        }
    }
    fin.close();
    fout.close();
}


#endif // TRANSLATOR_H
