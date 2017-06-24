#ifndef WORKWITHFILES_H
#define WORKWITHFILES_H

#include "fstream"
#include "iostream"
#include "sstream"

void AppendFromFileToFile(std::ifstream& from, std::ofstream& to)
{
  char symbol;
  from.clear();
  from.seekg(0);
  while(from.get(symbol))
    to.put(symbol);
  if(!from.eof() || !to)
    print("suka");
}


#endif // WORKWITHFILES_H
