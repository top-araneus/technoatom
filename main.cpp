#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <new>
#include <cstring>
#include "print.h"
#include "stack.h"
#include "arraytest.h"
#include "stacktest.h"
#include "smart_ptr.h"
#include "smart_ptr_test.h"

using namespace std;



Array<double> testfunc(Array<double> arr)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return arr;
}


//-----------------------------------
//! @fn main()
//! @brief Menu for CLI.
//! Access to I/O operations
//! with stack from keyboard.
//-----------------------------------
int main()
{

while(1)
{
   ArrayTest<double>* tests = new ArrayTest<double>;
   tests->TestAll();
    delete tests;
  ArrayTest<bool>* testsBool = new ArrayTest<bool>;
    testsBool->TestAll();
    delete testsBool;

    test<double>();

    Test_auto_ptr<int> test_auto;
    Test_unique_ptr<int> test_unique;
    Test_shared_ptr<int> test_shared;

    test_auto.TestAll();
    test_unique.TestAll();
    test_shared.TestAll();

    hack_ptrs<int>();
}
    getchar();
    return 0;
}
