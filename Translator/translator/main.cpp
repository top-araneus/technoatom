#include <QCoreApplication>
#include "translator.h"
#include "iostream"

int main(int argc, char *argv[])
{
    std::string str = "1qwe";
    str.erase(0,1);
    std::cout << str;

    return 0;
}
