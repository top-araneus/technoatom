//-----------------------------------
//! @file stacktest.h
//! Unit tests for Stack class
//!
//! team araneus, 2017
//-----------------------------------
#ifndef STACKTEST_H
#define STACKTEST_H
#include "stack.h"
#include "../utils/exception.h"
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
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    cout << "Starting stack test . . .: " << endl;
    //given for all test
    Stack<value_type>* stack;
    //-----------------------------------
    //!@brief Test 1. Create stack
    //-----------------------------------
    //when
    try
    {
        stack = new Stack<value_type>();
    }
    //then
    catch (Exception e)
    {
        if (e == EMemAllocError())
            cout << "Test 1 failed: EMemAllocError" << endl;
        else
            cout << "Test 1 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //!@brief Test 2. Add value 123 to stack.
    //-----------------------------------
    //when
    try
    {
        stack->push(static_cast<value_type>(123));
    }
    //then
    catch (Exception e)
    {
        if (e == EMemAllocError())
            cout << "Test 2 failed: EMemAllocError" << endl;
        else
            cout << "Test 2 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //!@brief Test 3. Get top value from stack
    //-----------------------------------
    value_type a;
    //when
    try
    {
        a = stack->pop();
    }
    //then
    catch (Exception e)
    {
        if (e == EStackIsEmpty())
            cout << "Test 3 failed: EStackIsEmpty" << endl;
        else
            cout << "Test 3 failed: exception code " << e << endl;
    }
    if (a != 123)
        cout << "Test 3 failed: a != 123, a = " << a << endl;
    //-----------------------------------
    //!@brief Test 4. Try to get smth from empty stack.
    //-----------------------------------
    //when
    try
    {
        a = stack->pop();
    }
    //then
    catch (Exception e)
    {

        if (e != EStackIsEmpty())
            cout << "Test 4 failed: exception code " << e << ", a = " << a << endl;
    }
    //-----------------------------------
    //!@brief Test 5. Add several elements
    //-----------------------------------
    //when
    try
    {
        stack->push(static_cast<value_type>(1));
        stack->push(static_cast<value_type>(2));
        stack->push(static_cast<value_type>(3));
    }
    //then
    catch (Exception e)
    {
        if (e == EMemAllocError())
            cout << "Test 5 failed: EMemAllocError" << endl;
        else
            cout << "Test 5 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //!@brief Test 6. Get top element without removing
    //-----------------------------------
    //when
    try
    {
        a = stack->top();
    }
    //then
    catch (Exception e)
    {
        if (e == EStackIsEmpty())
            cout << "Test 6 failed: EStackIsEmpty" << endl;
        else
            cout << "Test 6 failed: exception code " << e << endl;
    }
    if (a != static_cast<value_type>(3))
        cout << "Test 6 failed: a != 3, a = " << a << endl;
    //-----------------------------------
    //!@brief Test 7. Add more elements than stack capacity
    //-----------------------------------
    size_t cap;
    //when
    try
    {
        cap = stack->capacity();
        for (size_t i = 4; i<=4+cap; ++i)
            stack->push(static_cast<value_type>(i));

    }
    //then
    catch (Exception e)
    {
        if (e == EMemAllocError())
            cout << "Test 7 failed: EMemAllocError" << endl;
        else
            cout << "Test 7 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //! @brief Test 8. Assign stack to new variable
    //-----------------------------------

    try
    {
        //given
        Stack<value_type>* s2 = new Stack<value_type>();
        //when
        *s2 = *stack;
        //then
        if ( (s2->top() != stack->top()) || (s2 == stack) )
            cout << " 8: failed, s2 top = " << s2->top() << ", stack->top = " << stack->top() << endl;
        else
        {
            //when
            s2->pop();
            //then
            if (stack->top() == s2->top())
                cout << " 8: failed, s2 top = " << s2->top() << ", stack->top = " << stack->top() << endl;
        }
        delete s2;

    }
    catch(Exception e)
    {
        if (e == EMemAllocError())
            cout << "Test 8 failed: EMemAllocError" << endl;
        else
            cout << "Test 8 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //! @brief Test 9. Initialize variable by old stack
    //-----------------------------------
    try
    {
        //when
        Stack<value_type> s2 = *stack;
        //then
        if (s2.top() != stack->top())
            cout << " 9: failed, s2 top = " << s2.top() << ", stack->top = " << stack->top() << endl;
        else
        {
            s2.pop();
            if (stack->top() == s2.top())
                cout << " 9: failed, s2 top = " << s2.top() << ", stack->top = " << stack->top() << endl;
        }

    }
    catch(Exception e)
    {
        if (e == EMemAllocError())
            cout << "Test 9 failed: EMemAllocError" << endl;
        else
            cout << "Test 9 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //!@brief Test 10. Get all elements of stack
    //-----------------------------------
    value_type val;
    bool isEqual = true;
    //when
    try
    {
        for (size_t i = 4+cap; i>0; --i)
        {
            val = stack->pop();
            //then
            if (val != static_cast<value_type>(i))
            {
                isEqual = false;
                cout << "Test 10 failed: i == " << i << ", val == " << val << endl;
            }
        }
    }
    catch (Exception e)
    {

        if (e == EStackIsEmpty())
            cout << "Test 10 failed: EStackIsEmpty" << endl;
        else
            cout << "Test 10 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //! Test 11. Create dump file
    //-----------------------------------
    try
    {
        //when
//        stack->dump();
    }
    //then
    catch (Exception e)
    {
        if (e == EFileCreationError())
            cout << "Test 11 failed: EFileCreationError" << endl;
        else
            cout << "Test 11 failed: exception code " << e << endl;
    }
    //-----------------------------------
    //! Test 12. Delete stack
    //-----------------------------------
    //when
    try
    {
        delete stack;
    }
    //then
    catch(int e)
    {
        cout << "Test 12 failed: exception code " << e << endl;
    }

    cout << "Stack test ended. " << endl;
}



#endif // STACKTEST_H
