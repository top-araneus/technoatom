#include <QCoreApplication>
#include "translator.h"
#include "iostream"

int main(int argc, char *argv[])
{
    print("ja rodilsja <3\n");
    Translator("factorial.alu", "code.bin");
    Disassembler("code.bin", "disassembled.alu");
    //Translator(argv[1], argv[2]);
    print("ja sdoh ._.");

    return 0;
}
