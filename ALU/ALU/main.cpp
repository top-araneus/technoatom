#include <QCoreApplication>
#include "alu.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string filename = argv[1];
    ALU alu(filename);

    alu.Execute(5,4,2,2);
    cout << "x: " << alu.GetRegister(0) << "y: " << alu.GetRegister(1) << endl;
    return a.exec();
}
