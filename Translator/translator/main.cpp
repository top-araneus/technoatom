#include <QCoreApplication>
#include "translator.h"
#include "iostream"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string from(argv[1]);
    std::string to(argv[2]);
    cout << "started" << endl;
    Translator("..\\..\\source_code\\" + from, "..\\..\\bin_code\\" + to);
    cout << "done" << endl;

    return a.exec();
}
