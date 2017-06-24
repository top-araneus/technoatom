#include <QCoreApplication>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../../utils/print.h"
#include "transl.h"

/*void opa(std::ifstream& fin)
{
  int pos = fin.tellg();
  std::string a;
  fin >> a;
  print("in func /#\n",a);
  fin.seekg(pos);
}*/

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  std::string from(argv[1]);
  from = string("..\\..\\source_code\\") + from;
  std::string to(argv[2]);
  to = string("..\\..\\bin_code\\") + to;
  cout << "started" << endl;
  Translator transl(from, to);
  transl.FirstPass();
  transl.SecondPass();
  transl.ThirdPass();
  cout << "done" << endl;
  return a.exec();


/*  std::ifstream fin("../../source_code/sqrt.alu", std::ios_base::in);
  std::string a;
  fin >> a;
  print("/#\n",a);
  opa(fin);
  fin >> a;
  print("/#\n",a);


  return 1;// a.exec();*/
}
