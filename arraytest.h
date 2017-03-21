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
        defaultSize=TEST_SIZE;
        std::cout << "Starting array test . . ." << std::endl;
    }
    size_t defaultSize;
    void TestAll()
    {
        TestSquares();;
        TestSquaresOutRange();
        TestCopy(); //failed
        TestAssign(); //failed
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
                    throw Exception::ETestFailed;
                }
            }
        }
        catch(int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
                std::cout << "|.Test 1 failed: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
                std::cout << "|.Test 1 failed: out of range"<<std::endl;
            }
        }

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
            throw Exception::ETestFailed;
        }
        catch(int errorCode)
        {
            if(errorCode == Exception::EIndexOutOfRange)
            {
                e1 = true;
            }
            if(errorCode == Exception::ETestFailed)
            {
                std::cout << "Test 2.1 failed" << std::endl;
            }
        }
        try
        {
            //when
            (*testArray)[-1];
            throw Exception::ETestFailed;
        }
        catch(int errorCode)
        {
            if(errorCode == Exception::EIndexOutOfRange)
            {
                e2 = true;
            }
            if(errorCode == Exception::ETestFailed)
            {
                std::cout << "Test 2.2 failed" << std::endl;
            }
        }
        if(!(e1 && e2))
        {
            std::cout << "TestSquaresOutRange failed" << std::endl;
        }

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
                    throw Exception::ETestFailed;
                }
            }
            delete testarray;
            for (size_t i = 0; i < defaultSize; i++)
            {
                if ( clonearray[i] != static_cast<Type>(i) )
                {
                    std::cout << "|.expected value " << static_cast<Type>(i) << " and got " << clonearray[i]  << std::endl;
                    throw Exception::ETestFailed;
                }
            }

        }
        catch (int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
                std::cout << "|.Test 3 failed: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
                std::cout << "|.Test 3 failed: out of range"<<std::endl;
            }
            if(codeError == Exception::ETestFailed)
            {
                std::cout << "|.Test 3 failed"<<std::endl;
            }
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
                    throw Exception::ETestFailed;
                }
            }
            delete testarray;
            for (size_t i = 0; i < defaultSize; i++)
            {
                if ( clonearray[i] != static_cast<Type>(i) )
                {
                    throw Exception::ETestFailed;
                }
            }
        }
        catch (int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
                std::cout << "|.Test 4 failed: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
                std::cout << "|.Test 4 failed: out of range"<<std::endl;
            }
            if(codeError == Exception::ETestFailed)
            {
                std::cout << "|.Test 4 failed"<<std::endl;
            }
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
                throw Exception::ETestFailed;
            }
            for (int i = 0; i<2*defaultSize; ++i)
            {
                if (static_cast<Type>(i) != result[i])
                {
                    throw Exception::ETestFailed;
                }
            }

        }
        catch(int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
                std::cout << "|.Test 5 failed: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
                std::cout << "|.Test 5 failed: out of range"<<std::endl;
            }
            if(codeError == Exception::ETestFailed)
            {
                std::cout << "|.Test 5 failed"<<std::endl;
            }
        }
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
                throw Exception::ETestFailed;
            }

        }
        catch (int codeError)
        {

            if(codeError == Exception::EMemAllocError)
            {
                std::cout << "|.Test 6 failed: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
                std::cout << "|.Test 6 failed: out of range"<<std::endl;
            }
            if(codeError == Exception::ETestFailed)
            {
                std::cout << "|.Test 6 failed"<<std::endl;
            }
        }
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
                throw Exception::ETestFailed;
            }

            if((*testobj)[(*testobj).Size() -1 ] != static_cast<Type>(defaultSize - 1))
            {
                throw Exception::ETestFailed;
            }
            //when
            (*testobj).Insert(defaultSize/2,static_cast<Type>(defaultSize + 1));
            //then
            if ( (*testobj)[defaultSize/2] != static_cast<Type>(defaultSize + 1) || (*testobj).Size() != defaultSize + 2 )
            {
                throw Exception::ETestFailed;
            }
            if((*testobj)[defaultSize/2 + 1] != static_cast<Type>(defaultSize/2))
            {
                throw Exception::ETestFailed;
            }
            //when
            (*testobj).Insert(0,static_cast<Type>(defaultSize + 2));
            //then
            if ( (*testobj)[0] != static_cast<Type>(defaultSize + 2) || (*testobj).Size() != defaultSize + 3 )
            {
                throw Exception::ETestFailed;
            }
            if((*testobj)[1] != static_cast<Type>(0))
            {
                throw Exception::ETestFailed;
            }

        }
        catch (int codeError)
        {

            if(codeError == Exception::EMemAllocError)
            {
                std::cout << "|.Test 7 failed: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
                std::cout << "|.Test 7 failed: out of range"<<std::endl;
            }
            if(codeError == Exception::ETestFailed)
            {
                std::cout << "|.Test 7 failed"<<std::endl;
            }
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
                throw Exception::ETestFailed;
            }
            //when
            testobj->Erase(0);
            //then
            if( testobj->GetData() != nullptr || testobj->Size() != 0)
            {
                throw Exception::ETestFailed;
            }
        }
        catch(int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
                std::cout << "|.Test 8 failed: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
                std::cout << "|.Test 8 failed: out of range"<<std::endl;
            }
            if(codeError == Exception::ETestFailed)
            {
                std::cout << "|.Test 8 failed"<<std::endl;
            }
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
                    throw Exception::ETestFailed;
                }
            }
        }
        catch(int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
                std::cout << "|.Test 9 failed: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
                std::cout << "|.Test 9 failed: out of range"<<std::endl;
            }
            if(codeError == Exception::ETestFailed)
            {
                std::cout << "|.Test 9 failed"<<std::endl;
            }
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
                throw Exception::ETestFailed;
            }
            //when
            testobj->Resize(1);
            //then
            if ( (*testobj)[0] != static_cast<Type>(0) || testobj->Size() != 1)
            {
                throw Exception::ETestFailed;
            }
        }
        catch(int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
                std::cout << "|.Test 10 failed: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
                std::cout << "|.Test 10 failed: out of range"<<std::endl;
            }
            if(codeError == Exception::EBadSize)
            {
                std::cout << "|.Test 10 failed: badsize in argument"<<std::endl;
            }
            if(codeError == Exception::ETestFailed)
            {
                std::cout << "|.Test 10 failed"<<std::endl;
            }
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
        catch (int errorCode)
        {
            if (errorCode == Exception::EFileCreationError)
                std::cout << "Test 11 failed: got file creation error" << std::endl;
        }
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
                    throw Exception::ETestFailed;
            }
        }
        catch (int errorCode)
        {
            std::cout << "Test 12 failed" << std::endl;
        }

    }

};



#endif // ARRAYTEST_H
