#include <QCoreApplication>
#include "alu.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string filename = argv[1];
    ALU alu(filename);

    alu.Execute(5);
    cout << "x0: " << alu.GetRegister(0) << endl;
    return a.exec();
}
