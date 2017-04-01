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


    ArrayTest<double>* tests = new ArrayTest<double>;
    tests->TestAll();
    delete tests;

    ArrayTest<bool>* testsBool = new ArrayTest<bool>;
        testsBool->TestAll();
        delete testsBool;




    std::cout << std::endl;

    test<double>();

//	test_auto_ptr();
    Test_auto_ptr<int> test_auto;
    Test_unique_ptr<int> test_unique;
    Test_shared_ptr<int> test_shared;

/*test_auto.Assignment();
test_auto.Copy();
test_auto.Arrow();
test_unique.MoveAssignment();
test_unique.MoveCopy();
test_unique.Arrow();
test_shared.Copy();
test_shared.Assignment();
test_shared.Arrow();
test_shared.CountIncrease();
test_shared.CountDecreaseDelete();
test_shared.CountDecreaseAssignment();
test_shared.CountMove();*/
    test_auto.TestAll();
    test_unique.TestAll();
    test_shared.TestAll();
    getchar();
    return 0;
}
