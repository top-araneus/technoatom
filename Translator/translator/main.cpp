#include <QCoreApplication>
#include "translator.h"
#include "iostream"

int main(int argc, char *argv[])
{
    print("ja rodilsja <3\n");
	Translator("..\\source_code\\fact.alu", "..\\bin_code\\fact4.bin");
	Disassembler("..\\bin_code\\fact4.bin", "..\\desassembler_code\\fact.alu");
    //Translator(argv[1], argv[2]);
    print("ja sdoh ._.");

    return 0;
}
