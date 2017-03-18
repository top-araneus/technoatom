#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <new>
#include <cstring>

#include "exception.h"
#include "array_iter.h"
#include "stack.h"
#include "array.h"
#include "arraytest.h"
#include "stacktest.h"
using namespace std;




//-----------------------------------
//! @fn main()
//! @brief Menu for CLI.
//! Access to I/O operations
//! with stack from keyboard.
//-----------------------------------
int main()
{
    ArrayTest<double>* tests = new ArrayTest<double>;
    tests->TestAll();
    delete tests;

    test<double>();

    getchar();
    return 0;
}
