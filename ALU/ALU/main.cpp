#include "alu.h"
int main()
{
    std::string filename = "dva.bin";
    ALU alu(filename);

    alu.Execute(5);
    cout << "x:" << alu.GetRegister(0) << endl;
    return 0;
}
