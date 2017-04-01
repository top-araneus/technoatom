//-----------------------------------
//! @file arraytest.h
//! Unit tests for Array class
//!
//! team araneus, 2017
//-----------------------------------
#ifndef ARRAYTEST_H
#define ARRAYTEST_H
#include <iostream>
#include "array.h"

const size_t TEST_SIZE=100;

template<typename Type>
class ArrayTest
{
public:

    ArrayTest()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        defaultSize=TEST_SIZE;
        std::cout << "Starting array test . . ." << std::endl;
    }
    size_t defaultSize;
    void TestAll()
    {
        TestSquares();;
        TestSquaresOutRange();
        TestCopy();
        TestAssign();
        TestPlus();
        TestPush();
        TestInsert();
        TestErase();
        TestClear();
        TestResize();
        TestDump();
        TestInit();
    }
    ~ArrayTest()
    {
        std::cout << "Tests ended." << std::endl << std::endl;
    }

    //-----------------------------------
    //! @brief Testing of correct getting elements by indexes
    //! with operator[] and assignment
    //-----------------------------------
    void TestSquares()
    {
        //given
        Array<Type>* testArray = new Array<Type>(defaultSize);
        try
        {
            //when
            for(size_t i = 0; i < defaultSize; i++)
            {
                (*testArray)[i] = static_cast<Type>(i);
            }
            //then
            for(size_t i = 0; i < defaultSize; i++)
            {
                if( (*testArray)[i] != static_cast<Type>(i))
                {
                    std::cout << "|.Test 1 failed: expected " << static_cast<Type>(i) << " and got " << testArray[i]  << std::endl;
                    throw ETestFailed(__FL__);
                }
            }
        }
        catch(Exception error)
        {
            print("|.Test 1 failed. \n/#", error);
        }
        delete testArray;
    }
    //-----------------------------------
    //! @brief Testing of correct catching exceptions when index is out of range
    //-----------------------------------
    void TestSquaresOutRange()
    {
        // given
        Array<Type>* testArray = new Array<Type>(defaultSize);
        bool e1 = false, e2 = false;
        try
        {
            //when
            (*testArray)[defaultSize];
            throw ETestFailed(__FL__);
        }
        //then
        catch(Exception error)
        {
            if(error == EIndexOutOfRange())
            {
                e1 = true;
            }
            if(error == ETestFailed())
            {
                print("|.Test 2.1 failed. \n/#", error);
            }
        }
        try
        {
            //when
            (*testArray)[-1];
            throw ETestFailed(__FL__);
        }
        //then
        catch(Exception error)
        {
            if(error == EIndexOutOfRange())
            {
                e2 = true;
            }
            if(error == ETestFailed())
            {
                print("|.Test 2.2 failed. \n/#", error);
            }
        }
        if(!(e1 && e2))
        {
            std::cout << "TestSquaresOutRange failed" << std::endl;
        }
        delete testArray;

    }
    //-----------------------------------
    //! @brief Testing copy constructor
    //-----------------------------------
    void TestCopy()
    {
        //given
        Array<Type>* testarray = new Array<Type>(defaultSize);
        for (size_t i = 0; i < defaultSize; i++)
        {
            (*testarray)[i] = static_cast<Type>(i);
        }
        try
        {
            //when
            Array<Type> clonearray = *testarray;
            //then
            for (size_t i = 0; i < defaultSize; i++)
            {
                if ((*testarray)[i] != clonearray[i] )
                {
                    std::cout << "|.expected value " << (*testarray)[i] << " and got " << clonearray[i]  << std::endl;
                    throw ETestFailed(__FL__);
                }
            }
            delete testarray;
            for (size_t i = 0; i < defaultSize; i++)
            {
                if ( clonearray[i] != static_cast<Type>(i) )
                {
                    std::cout << "|.expected value " << static_cast<Type>(i) << " and got " << clonearray[i]  << std::endl;
                    throw ETestFailed(__FL__);
                }
            }

        }
        catch (Exception error)
        {
            print("|.Test 3 failed. \n/#", error);
        }
    }
    //-----------------------------------
    //! @brief Testing assignment operator
    //-----------------------------------
    void TestAssign()
    {
        //given
        Array<Type>* testarray = new Array<Type>(defaultSize);
        for (size_t i = 0; i < defaultSize; i++)
        {
            (*testarray)[i] = static_cast<Type>(i);
        }
        try
        {
            Array<Type> clonearray;
            //when
            clonearray = *testarray;
            //then
            for (size_t i = 0; i < defaultSize; i++)
            {
                if ((*testarray)[i] != clonearray[i])
                {
                    throw ETestFailed(__FL__);
                }
            }
            delete testarray;
            for (size_t i = 0; i < defaultSize; i++)
            {
                if ( clonearray[i] != static_cast<Type>(i) )
                {
                    throw ETestFailed(__FL__);
                }
            }
        }
        catch (Exception error)
        {
            print("|.Test 4 failed. \n/#", error);
        }
    }
    //-----------------------------------
    //! @brief Testing operator plus
    //-----------------------------------
    void TestPlus()
    {
        //given
        Array<Type>* f = new Array<Type>(defaultSize);
        Array<Type>* s = new Array<Type>(defaultSize);
        Array<Type> first = *f;
        Array<Type> second = *s;
        for (int i = 0; i < defaultSize; ++i)
        {
            first[i] = static_cast<Type>(i);
        }
        for (int i = 0; i<defaultSize; ++i)
        {
            second[i] = static_cast<Type>(i + defaultSize);
        }
        try
        {
            //when
            Array<Type> result = first + second;
            //then
            if (result.Size() != 2*defaultSize)
            {
                throw ETestFailed(__FL__);
            }
            for (int i = 0; i<2*defaultSize; ++i)
            {
                if (static_cast<Type>(i) != result[i])
                {
                    throw ETestFailed(__FL__);
                }
            }

        }
        catch (Exception error)
        {
            print("|.Test 5 failed. \n/#", error);
        }
        delete f;
        delete s;
    }
    //-----------------------------------
    //! @brief Testing adding elements in the end of Array
    //-----------------------------------
    void TestPush()
    {
        //given
        Array<Type>* array = new Array<Type>(defaultSize);
        for (int i = 0; i<defaultSize; ++i)
        {
            (*array)[i] = static_cast<Type>(i);
        }
        Type elem = static_cast<Type>(defaultSize);
        try
        {
            //when
            array->PushBack(elem);
            //then
            if ((*array)[defaultSize] != static_cast<Type>(defaultSize))
            {
                throw ETestFailed(__FL__);
            }

        }
        catch (Exception error)
        {
            print("|.Test 6 failed. \n/#", error);
        }
        delete array;
    }
    //-----------------------------------
    //! @brief Testing inserting elements by defined indexes. Cheking borders of Array
    //-----------------------------------
    void TestInsert()
    {
        try
        {
            //given
            Array<Type>* testobj = new Array<Type>(defaultSize);
            for (int i = 0; i < defaultSize; i++)
            {
                (*testobj)[i] = static_cast<Type>(i);
            }
            //when
            (*testobj).Insert(defaultSize - 1,static_cast<Type>(defaultSize));
            //then
            if ( (*testobj)[defaultSize - 1] != static_cast<Type>(defaultSize) || (*testobj).Size() != defaultSize + 1 )
            {
                delete testobj;
                throw ETestFailed(__FL__);
            }

            if((*testobj)[(*testobj).Size() -1 ] != static_cast<Type>(defaultSize - 1))
            {
                delete testobj;
                throw ETestFailed(__FL__);
            }
            //when
            (*testobj).Insert(defaultSize/2,static_cast<Type>(defaultSize + 1));
            //then
            if ( (*testobj)[defaultSize/2] != static_cast<Type>(defaultSize + 1) || (*testobj).Size() != defaultSize + 2 )
            {
                delete testobj;
                throw ETestFailed(__FL__);
            }
            if((*testobj)[defaultSize/2 + 1] != static_cast<Type>(defaultSize/2))
            {
                delete testobj;
                throw ETestFailed(__FL__);
            }
            //when
            (*testobj).Insert(0,static_cast<Type>(defaultSize + 2));
            //then
            if ( (*testobj)[0] != static_cast<Type>(defaultSize + 2) || (*testobj).Size() != defaultSize + 3 )
            {
                delete testobj;
                throw ETestFailed(__FL__);
            }
            if((*testobj)[1] != static_cast<Type>(0))
            {
                delete testobj;
                throw ETestFailed(__FL__);
            }
            delete testobj;

        }
        catch (Exception error)
        {
            print("|.Test 7 failed. \n/#", error);
        }
    }
    //-----------------------------------
    //! @brief Testing erasing of elements by defined index
    //-----------------------------------
    void TestErase()
    {
        try
        {
            //given
            Array<Type>* testobj = new Array<Type>(defaultSize);
            for (int i = 0; i < defaultSize; i++)
            {
                (*testobj)[i] = static_cast<Type>(i);
            }
            //when
            for (int i = 0; i < defaultSize - 1; i++)
            {
                testobj->Erase(0);
            }
            //then
            if ( (*testobj)[0] != static_cast<Type>(defaultSize-1) || testobj->Size() != 1 )
            {
                delete testobj;
                throw ETestFailed(__FL__);
            }
            //when
            testobj->Erase(0);
            //then
            if( testobj->GetData() != nullptr || testobj->Size() != 0)
            {
                delete testobj;
                throw ETestFailed(__FL__);
            }
            delete testobj;
        }
        catch (Exception error)
        {
            print("|.Test 8 failed. \n/#", error);
        }
    }
    //-----------------------------------
    //! @brief Testing clearing
    //-----------------------------------
    void TestClear()
    {
        try
        {
            //given
            Array<Type>* testobj = new Array<Type>(defaultSize);
            for (int i = 0; i < defaultSize; i++)
            {
                (*testobj)[i] = static_cast<Type>(i);
            }
            //when
            testobj->Clear();
            //then
            for (int i = 0; i < defaultSize; i++)
            {
                if ( (*testobj)[i] != static_cast<Type>(0))
                {
                    delete testobj;
                    throw ETestFailed(__FL__);
                }
            }
            delete testobj;
        }
        catch (Exception error)
        {
            print("|.Test 9 failed. \n/#", error);
        }
    }
    //-----------------------------------
    //! @brief Testing changing size of Array with border-case
    //-----------------------------------
    void TestResize()
    {
        try
        {
            //given
            Array<Type>* testobj = new Array<Type>;
            //when
            testobj->Resize(defaultSize);
            //then
            for (int i = 0; i < defaultSize; i++)
            {
                (*testobj)[i] = static_cast<Type>(i);
            }
            if ( (*testobj)[defaultSize - 1] != static_cast<Type>(defaultSize - 1) || testobj->Size() != defaultSize)
            {
                delete testobj;
                throw ETestFailed(__FL__);
            }
            //when
            testobj->Resize(1);
            //then
            if ( (*testobj)[0] != static_cast<Type>(0) || testobj->Size() != 1)
            {
                delete testobj;
                throw ETestFailed(__FL__);
            }
            delete testobj;
        }
        catch (Exception error)
        {
            print("|.Test 10 failed. \n/#", error);
        }
    }
    //-----------------------------------
    //! @brief Testing operator << and correction of Dump
    //-----------------------------------
    void TestDump()
    {
        //given
        Array<Type>* testobj = new Array<Type>(10);
        for (int i=0; i<10; i++)
        {
            (*testobj)[i] = static_cast<Type>(i);
        }
        //when
        try
        {
            testobj->Dump();
        }
        //then
        catch (Exception error)
        {
            print("|.Test 11 failed. \n/#", error);
        }
        delete testobj;
    }
    //-----------------------------------
    //! @brief Testing placement&initializing operator new
    //-----------------------------------
    void TestInit()
    {
        try
        {
            //given
            Array<int> test(10);
            //when
            new(&test,0) Array<int>(test);
            //then
            for (int i = 0; i < 10; i++)
            {
                if (test[i] != 0)
                    throw ETestFailed(__FL__);
            }
        }
        catch (Exception error)
        {
            print("|.Test 12 failed. \n/#", error);
        }

    }

};



#endif // ARRAYTEST_H
