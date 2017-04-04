#include <QCoreApplication>
#include "alu.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    a.applicationDirPath();
    ALU<int> alu("fact4.bin");
    alu.SetRegister(0, 8);
    alu.Execute();
    cout << "x0: " << alu.GetRegister(0) << endl;

    getchar();

    return a.exec();
}
