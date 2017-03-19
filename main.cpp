#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <new>
#include <cstring>
#include "print.h"
#include "stack.h"
#include "array.h"
#include "arraytest.h"
#include "stacktest.h"
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
/*    ArrayTest<double>* tests = new ArrayTest<double>;
    tests->TestAll();
    delete tests;*/

    Array<bool> st(18);
    st[12] = true;
    bool a = false;
    a = st[12];
    std::cout << st;
 /*   Array<double> array = {1.4, 8.8};
   std::cout << array << std::endl;*/


/*    std::cout << std::endl;

    test<double>();
*/
    getchar();
    return 0;
}
