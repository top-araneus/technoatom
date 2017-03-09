#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include "Stack.h"
#include "array.h"
#include "arraytest.h"
using namespace std;


//-----------------------------------
//! @fn test()
//! @brief 11 unit tests for stack.
//! Checks creating, appending, getting elements,
//! throwing and catching exceptions,
//! enlarging container size, making dumps,
//! copying stack to stack.
//-----------------------------------

template<typename value_type>
void test()
{
    cout << "\nStarting test . . .: " << endl;
    Stack<value_type>* stack;
    //-----------------------------------
    //!@brief Test 1. Create stack
    //-----------------------------------
    try
    {
      stack = new Stack<value_type>();
      cout << " 1: passed" << endl;
    }
    catch (int e)
    {
        if (e == Exception::EMemAllocError)
            cout << "Test 1 failed: EMemAllocError" << endl;
        else
            cout << "Test 1 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //!@brief Test 2. Add value 123 to stack.
    //-----------------------------------
    try
    {
        stack->push(static_cast<value_type>(123));
        cout << " 2: passed" << endl;
    }
    catch (int e)
    {
        if (e == Exception::EMemAllocError)
            cout << "Test 2 failed: EMemAllocError" << endl;
        else
            cout << "Test 2 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //!@brief Test 3. Get top value from stack
    //-----------------------------------
    value_type a;
    try
    {
        a = stack->pop();
    }
    catch (int e)
    {
        if (e == Exception::EStackIsEmpty)
            cout << "Test 3 failed: EStackIsEmpty" << endl;
        else
            cout << "Test 3 failed: exception code " << e << endl;
    }
    if (a != 123)
        cout << "Test 3 failed: a != 123, a = " << a << endl;
    else
        cout << " 3: passed" << endl;
    //-----------------------------------
    //!@brief Test 4. Try to get smth from empty stack.
    //-----------------------------------
    try
    {
        a = stack->pop();
    }
    catch (int e)
    {
        if (e != Exception::EStackIsEmpty)
            cout << "Test 4 failed: exception code " << e << ", a = " << a << endl;
        else
            cout << " 4: passed" << endl;
    }
    //-----------------------------------
    //!@brief Test 5. Add several elements
    //-----------------------------------
    try
    {
        stack->push(static_cast<value_type>(1));
        stack->push(static_cast<value_type>(2));
        stack->push(static_cast<value_type>(3));
        cout << " 5: passed" << endl;
    }
    catch (int e)
    {
        if (e == Exception::EMemAllocError)
            cout << "Test 5 failed: EMemAllocError" << endl;
        else
            cout << "Test 5 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //!@brief Test 6. Get top element without removing
    //-----------------------------------
    try
    {
        a = stack->top();
    }
    catch (int e)
    {
        if (e == Exception::EStackIsEmpty)
            cout << "Test 6 failed: EStackIsEmpty" << endl;
        else
            cout << "Test 6 failed: exception code " << e << endl;
    }
    if (a != static_cast<value_type>(3))
        cout << "Test 6 failed: a != 3, a = " << a << endl;
    else
        cout << " 6: passed" << endl;
    //-----------------------------------
    //!@brief Test 7. Add more elements than stack capacity
    //-----------------------------------
    size_t cap;
    try
    {
        cap = stack->capacity();
        for (size_t i = 4; i<=4+cap; ++i)
            stack->push(static_cast<value_type>(i));
        cout << " 7: passed" << endl;

    }
    catch (int e)
    {
        if (e == Exception::EMemAllocError)
            cout << "Test 7 failed: EMemAllocError" << endl;
        else
            cout << "Test 7 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //! @brief Test 8. Assign stack to new variable
    //-----------------------------------
    try
    {
        Stack<value_type>* s2 = new Stack<value_type>();
        *s2 = *stack;
        if ( (s2->top() != stack->top()) || (s2 == stack) )
            cout << " 8: failed, s2 top = " << s2->top() << ", stack->top = " << stack->top() << endl;
        else
        {
            s2->pop();
            if (stack->top() == s2->top())
                    cout << " 8: failed, s2 top = " << s2->top() << ", stack->top = " << stack->top() << endl;
            else
            {
                cout << " 8: passed" << endl;
            }
        }

    }
    catch(int e)
    {
        if (e == Exception::EMemAllocError)
            cout << "Test 8 failed: EMemAllocError" << endl;
        else
            cout << "Test 8 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //! @brief Test 9. Initialize variable by old stack
    //-----------------------------------
    try
    {
        Stack<value_type> s2 = *stack;
        if (s2.top() != stack->top())
            cout << " 9: failed, s2 top = " << s2.top() << ", stack->top = " << stack->top() << endl;
        else
        {
            s2.pop();
            if (stack->top() == s2.top())
                    cout << " 9: failed, s2 top = " << s2.top() << ", stack->top = " << stack->top() << endl;
            else
            {
                cout << " 9: passed" << endl;
            }
        }

    }
    catch(int e)
    {
        if (e == Exception::EMemAllocError)
            cout << "Test 8 failed: EMemAllocError" << endl;
        else
            cout << "Test 8 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //!@brief Test 10. Get all elements of stack
    //-----------------------------------
    value_type val;
    bool isEqual = true;
    try
    {
        for (size_t i = 4+cap; i>0; --i)
        {
            val = stack->pop();
            if (val != static_cast<value_type>(i))
            {
                isEqual = false;
                cout << "Test 10 failed: i == " << i << ", val == " << val << endl;
            }
        }
    }
    catch (int e)
    {

        if (e == Exception::EStackIsEmpty)
            cout << "Test 10 failed: EStackIsEmpty" << endl;
        else
            cout << "Test 10 failed: exception code " << e << endl;
    }
    if (isEqual)
        cout << "10: passed" << endl;
    //-----------------------------------
    //! Test 11. Create dump file
    //-----------------------------------
    try
    {
    stack->dump();
    cout << "11: passed" << endl;
    }
    catch (int e)
    {
        if (e == Exception::EFileCreationError)
            cout << "Test 11 failed: EFileCreationError" << endl;
        else
            cout << "Test 11 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //! Test 12. Delete stack
    //-----------------------------------
    try
    {
    delete stack;
        cout << "12: passed" << endl;
    }
    catch(int e)
    {
        cout << "Test 12 failed: exception code " << e << endl;
    }
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

    Stack<double>* stack = new Stack<double>();
    char cmd = '\0';  //!< command buffer

    while (cmd != 'e')
    {
        cout << "u for unit test\n"
                "m for manual input\n"
                "o for manual output\n"
                "c for pop all elements\n"
                "e for exit\n>";
        cin >> cmd;
        if (cmd == 'm')
        {
            cout << "Type numbers to add in stack:\n";
            char add = 'y';
            int buffer = 0;
            while (add == 'y')
            {
                cout << ">";
                cin >> buffer;
                stack->push(buffer);
                cout << "Continue? (y/n): ";
                cin >> add;
            }
            stack->dump();
        }
        else if (cmd == 'o')
        {
            cout << "What's in the box?" << endl;
            char getNew = 'y';
            while (getNew == 'y')
            {
                cout << "Remove top element? (y/n): ";
                cin >> getNew;
                if (getNew == 'y')
                    try
                {
                    cout << "Top element was: " << stack->pop() << endl;
                }
                catch (int e)
                {
                    if (e == Exception::EStackIsEmpty)
                    {
                        cout << "Stack is empty!" << endl;
                        getNew = 'n';
                    }
                }
            }
            stack->dump();
        }
        else if (cmd == 'c')
        {
            cout << "Stack contained: ";
            size_t size = stack->size();
            for (int i = size; i>0; --i)
            {
                cout << stack->pop() << " ";
            }
            cout << endl;
            stack->dump();
        }
        else if (cmd == 'u')
        {
            test<double>();
        }
    }
    return 0;
}
