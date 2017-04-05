#include <QCoreApplication>
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
    while (fin.read((char*)&buff, sizeof(buff)))
    {
        switch(buff)
        {
            case EXC:
                cout << "invalid instruction EXC (0) in code" << endl;
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


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string from(argv[1]);
    std::string to(argv[2]);
    cout << "started" << endl;
    Disassembler("..\\..\\bin_code\\" + from, "..\\..\\disassembler_code\\" + to);
    cout << "done" << endl;

    return a.exec();
}
