#ifndef ARRAYTEST_H
#define ARRAYTEST_H
#include <iostream>
#include "arraytest.h"
#include "array.h"
#include "exception.h"

const size_t TEST_SIZE=100;

template<typename Type>
class ArrayTest
{
public:
    ArrayTest()
    {
        defaultSize=TEST_SIZE;
        std::cout << "Tests started . . ." << std::endl;
    }
    size_t defaultSize;
    void TestAll()
    {
       std::cout << "Starting TestSquares" << std::endl;
       TestSquares();
	   std::cout << "\n\n";
       std::cout << "Starting TestSquaresOutRange" << std::endl;
       TestSquaresOutRange();
       std::cout << "\n\n";
       std::cout << "Starting TestCopy" << std::endl;
       TestCopy();
	   std::cout << "\n\n";
       std::cout << "Starting TestAssign" << std::endl;
       TestAssign();
	   std::cout << "\n\n";
	   std::cout << "Starting TestResize" << std::endl;
	   TestResize();
	   std::cout << "\n\n";
       std::cout << "Starting TestPlus" << std::endl;
       TestPlus();
	   std::cout << "\n\n";
       std::cout << "Starting TestPush" << std::endl;
       TestPush();
	   std::cout << "\n\n";
	   std::cout << "Starting TestInsert" << std::endl;
	   TestInsert();
	   std::cout << "\n\n";
	   std::cout << "Starting TestErase" << std::endl;
	   TestErase();
       std::cout << "\n\n";
       std::cout << "Starting TestClear" << std::endl;
       TestClear();
       std::cout << "\n\n";
       std::cout << "Starting TestDump" << std::endl;
       TestDump();
	   std::cout << "\n\n";
	   std::cout << "Starting TestInit" << std::endl;
	   TestInit();
    }
    //-----------------------------------
    //! @brief Testing of correct getting elements by indexes
    //! with operator[] and assignment
    //-----------------------------------
    void TestSquares()
    {
        std::string status = "Test[] passed";
		std::cout << "Given Array[" << defaultSize << "]" << std::endl;
		std::cout << "|.When filled by values (0.." << defaultSize-1 << ")" << std::endl;
        try
        {
            Array<Type>* testArray = new Array<Type>(defaultSize);
            for(size_t i = 0; i < defaultSize; i++)
            {
                (*testArray)[i] = static_cast<Type>(i);
            }
            for(size_t i=0;i<defaultSize;i++)
            {
                if( (*testArray)[i] != static_cast<Type>(i))
                {
					std::cout << "|.then expected " << static_cast<Type>(i) << " and got " << testArray[i]  << std::endl;
                    throw Exception::ETestFailed;
                }
            }
			std::cout << "|.then got Array with values (0.." << defaultSize-1 << ")" << std::endl;
        }
        catch(int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
				std::cout << "|.then got exception: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
				std::cout << "|.then got exception: out of range"<<std::endl;
            }
            status = "Test[] failed";
        }
        std::cout << status << std::endl;

    }
    //-----------------------------------
    //! @brief Testing of correct catching exceptions when index is out of range
    //-----------------------------------
    void TestSquaresOutRange()
    {
        Array<Type>* testArray = new Array<Type>(defaultSize);
        std::cout << "Given Array[" << defaultSize << "]" << std::endl;
        // given
        bool e1 = false, e2 = false;
        try
        {
            std::cout << "When getting element with index " << defaultSize << "" << std::endl;
            (*testArray)[defaultSize];
            std::cout << "then didn't catch exception!" << std::endl;
        }
        catch(int errorCode)
        {
            if(errorCode == Exception::EIndexOutOfRange)
            {
                std::cout << "then got exception EIndexOutOfRange" << std::endl;
                e1 = true;
            }
        }
        try
        {
            std::cout << "When getting element with index -1" << std::endl;
            (*testArray)[-1];
            std::cout << "then didn't catch exception!" << std::endl;
        }
        catch(int errorCode)
        {
            if(errorCode == Exception::EIndexOutOfRange)
            {
                std::cout << "then got exception EIndexOutOfRange" << std::endl;
                e2 = true;
            }
        }
        if(e1 && e2)
        {
            std::cout << "TestSquaresOutRange passed" << std::endl;
        }
        else
        {
            std::cout << "TestSquaresOutRange failed" << std::endl;
        }

    }
    //-----------------------------------
    //! @brief Testing copy constructor
    //-----------------------------------
    void TestCopy()
    {
        std::string status = "Test: copy constructor passed";
        Array<Type>* testarray = new Array<Type>(defaultSize);
        for (size_t i = 0; i < defaultSize; i++)
        {
            (*testarray)[i] = static_cast<Type>(i);
        }
		std::cout << "|.Given array with values (0.." << defaultSize-1 << ")" << std::endl;
		std::cout << "|.When copied it to new array" << std::endl;
        try
        {
            Array<Type> clonearray = *testarray;
            for (size_t i = 0; i < defaultSize; i++)
            {
                if ((*testarray)[i] != clonearray[i])
                {
					std::cout << "|.then expected value" << (*testarray)[i] << " and got " << clonearray[i]  << std::endl;
                    throw Exception::ETestFailed;
                }
            }
            delete testarray;
            for (size_t i = 0; i < defaultSize; i++)
            {
                if ( clonearray[i] != static_cast<Type>(i) )
                {
					std::cout << "|.then expected value" << static_cast<Type>(i) << " and got " << clonearray[i]  << std::endl;
                    throw Exception::ETestFailed;
                }
			}
			std::cout << "|.then expected values 0.." << defaultSize-1 << " and got them"  << std::endl;

        }
        catch (int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
				std::cout << "|.then got exception: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
				std::cout << "|.then got exception: out of range"<<std::endl;
            }
            status = "Test: copy constructor failed";
        }
        std::cout << status << std::endl;
    }
    //-----------------------------------
    //! @brief Testing assignment operator
    //-----------------------------------
    void TestAssign()
    {
        std::string status = "Test assignment passed";
        Array<Type>* testarray = new Array<Type>(defaultSize);
        for (size_t i = 0; i < defaultSize; i++)
        {
            (*testarray)[i] = static_cast<Type>(i);
        }
		std::cout << "|.Given array with values (0.." << defaultSize-1 << ")" << std::endl;
		std::cout << "|.When assigned it to new array" << std::endl;
        try
        {
            Array<Type> clonearray;
            clonearray = *testarray;
            for (size_t i = 0; i < defaultSize; i++)
            {
                if ((*testarray)[i] != clonearray[i])
                {
					std::cout << "|.then expected value" << (*testarray)[i] << " and got " << clonearray[i]  << std::endl;
                    throw Exception::ETestFailed;
                }
            }
            delete testarray;
            for (size_t i = 0; i < defaultSize; i++)
            {
                if ( clonearray[i] != static_cast<Type>(i) )
                {
					std::cout << "|.then expected value" << static_cast<Type>(i) << " and got " << clonearray[i]  << std::endl;
                    throw Exception::ETestFailed;
                }
			}
			std::cout << "|.then expected values 0.." << defaultSize-1 << " and got them"  << std::endl;
        }
        catch (int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
				std::cout << "|.then got exception: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
				std::cout << "|.then got exception: out of range"<<std::endl;
            }
            status = "Test assignment failed";
        }
        std::cout << status << std::endl;
    }
    //-----------------------------------
    //! @brief Testing operator plus
    //-----------------------------------
    void TestPlus()
    {
        std::string status = "Test concatenation passed";
        Array<Type>* f = new Array<Type>(defaultSize);
        Array<Type>* s = new Array<Type>(defaultSize);
        Array<Type> first = *f;
        Array<Type> second = *s;
		std::cout << "|.Given arrays with values (0.." << defaultSize-1 << ") and (" << defaultSize << ".." << 2*defaultSize-1 << ")" << std::endl;
        for (int i = 0; i < defaultSize; ++i)
        {
            first[i] = static_cast<Type>(i);
        }
        for (int i = 0; i<defaultSize; ++i)
        {
            second[i] = static_cast<Type>(i + defaultSize);
        }
		std::cout << "|.When concatenated it to new array" << std::endl;
        try
        {
            Array<Type> result = first + second;
            if (result.Size() != 2*defaultSize)
            {
				std::cout << "|.then expected size" << 2*defaultSize << " and got " << result.Size()  << std::endl;
                throw Exception::ETestFailed;
            }
            for (int i = 0; i<2*defaultSize; ++i)
            {
                if (static_cast<Type>(i) != result[i])
                {
					std::cout << "|.then expected value" << static_cast<Type>(i) << " and got " << result[i]  << std::endl;
                    throw Exception::ETestFailed;
                }
            }
			std::cout << "|.then expected values 0.." << 2*defaultSize-1 << " and got them"  << std::endl;

        }
        catch(int codeError)
        {
            if(codeError == Exception::EMemAllocError)
            {
				std::cout << "|.then got exception: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
				std::cout << "|.then got exception: out of range"<<std::endl;
            }
            status = "Test: copy constructor failed";
        }
        std::cout << status << std::endl;
    }
    //-----------------------------------
    //! @brief Testing adding elements in the end of Array
    //-----------------------------------
    void TestPush()
    {
        std::string status = "Test pushing passed";
		std::cout << "|.Given array with values (0.." << defaultSize-1 << ") and variable == " << defaultSize << "" << std::endl;
        Array<Type>* array = new Array<Type>(defaultSize);
        for (int i = 0; i<defaultSize; ++i)
        {
            (*array)[i] = static_cast<Type>(i);
        }
		std::cout << "|.When pushing the variable back in array" << std::endl;
        Type elem = static_cast<Type>(defaultSize);
        try
        {
            array->PushBack(elem);
            if ((*array)[defaultSize] != static_cast<Type>(defaultSize))
            {
				std::cout << "|.then expected value" << defaultSize << " and got " << (*array)[defaultSize]  << std::endl;
                throw Exception::ETestFailed;
            }
			std::cout << "|.then expected value " << defaultSize << " and got it"  << std::endl;

        }
        catch (int codeError)
        {

            if(codeError == Exception::EMemAllocError)
            {
				std::cout << "|.then got exception: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
				std::cout << "|.then got exception: out of range"<<std::endl;
            }
            status = "Test pushing failed";
        }
        std::cout << status << std::endl;
    }
    //-----------------------------------
    //! @brief Testing inserting elements by defined indexes. Cheking borders of Array
    //-----------------------------------
	void TestInsert()
	{
		std::string status = "Test pushing passed";
		try
		{
			std::cout << "|.Given array with values (0.." << defaultSize-1 << ") and variable == " << defaultSize << "" << std::endl;
			Array<Type>* testobj = new Array<Type>(defaultSize);
			for (int i = 0; i < defaultSize; i++)
			{
				(*testobj)[i] = static_cast<Type>(i);
			}

			std::cout << "|.When inserted in " << defaultSize-1 << " index " <<std::endl;
			(*testobj).Insert(defaultSize - 1,static_cast<Type>(defaultSize));
			std::cout << "|.then excepted value " << static_cast<Type>(defaultSize) << " and got ";
			if ( (*testobj)[defaultSize - 1] != static_cast<Type>(defaultSize) || (*testobj).Size() != defaultSize + 1 )
			{
				std::cout << (*testobj)[defaultSize -1] <<std::endl;
				throw Exception::ETestFailed;
			}
			std::cout << (*testobj)[defaultSize -1] <<std::endl;

			if((*testobj)[(*testobj).Size() -1 ] != static_cast<Type>(defaultSize - 1))
			{
				throw Exception::ETestFailed;
			}

			std::cout << "|.When inserted in " << defaultSize/2 << " index "<<std::endl;
			(*testobj).Insert(defaultSize/2,static_cast<Type>(defaultSize + 1));
			std::cout << "|.then excepted value " << static_cast<Type>(defaultSize + 1) <<" and got ";
			if ( (*testobj)[defaultSize/2] != static_cast<Type>(defaultSize + 1) || (*testobj).Size() != defaultSize + 2 )
			{
				std::cout << (*testobj)[defaultSize/2]<<std::endl;;
				throw Exception::ETestFailed;
			}
			std::cout << (*testobj)[defaultSize/2]<<std::endl;;
			if((*testobj)[defaultSize/2 + 1] != static_cast<Type>(defaultSize/2))
			{
				throw Exception::ETestFailed;
			}

			std::cout << "|.When inserted in 0 index \n";
			(*testobj).Insert(0,static_cast<Type>(defaultSize + 2));
			std::cout << "|.then excepted value " << static_cast<Type>(defaultSize + 2) <<" and got ";
			if ( (*testobj)[0] != static_cast<Type>(defaultSize + 2) || (*testobj).Size() != defaultSize + 3 )
			{
				std::cout << (*testobj)[0] <<std::endl;
				throw Exception::ETestFailed;
			}
			std::cout << (*testobj)[0] <<std::endl;;

			if((*testobj)[1] != static_cast<Type>(0))
			{
				throw Exception::ETestFailed;
			}

		}
		catch (int codeError)
		{

			if(codeError == Exception::EMemAllocError)
			{
				std::cout << "|.then got exception: memory allocation error"<<std::endl;
			}
			if(codeError == Exception::EIndexOutOfRange)
			{
				std::cout << "|.then got exception: out of range"<<std::endl;
			}
			status = "Test pushing failed";
		}
		std::cout << status << std::endl;

	}
    //-----------------------------------
    //! @brief Testing erasing of elements by defined index
    //-----------------------------------
	void TestErase()
	{
		std::string status = "Test Erase passed";
		try
		{
			std::cout << "|.Given array with values (0.." << defaultSize-1 << ")" << std::endl;
			std::cout << "|.When inserted "<<defaultSize<<" elements and removed "<<defaultSize-1<<" from its" << std::endl;
			Array<Type>* testobj = new Array<Type>(defaultSize);
			for (int i = 0; i < defaultSize; i++)
			{
				(*testobj)[i] = static_cast<Type>(i);
			}
			for (int i = 0; i < defaultSize - 1; i++)
			{
				testobj->Erase(0);
			}
			std::cout << "|.then expected that in 0 index will be " <<  static_cast<Type>(defaultSize -1 ) <<std::endl;
			std::cout << "|.and got " << (*testobj)[0] <<std::endl;
			if ( (*testobj)[0] != static_cast<Type>(defaultSize-1) || testobj->Size() != 1 )
			{
				throw Exception::ETestFailed;
			}
			std::cout << "|.When deleted last element " <<std::endl;
			testobj->Erase(0);
			std::cout << "|.then expected that pointer will be nullptr and got "<<testobj->GetData() << std::endl;
			if( testobj->GetData() != nullptr || testobj->Size() != 0)
			{
				throw Exception::ETestFailed;
			}
		}
		catch(int codeError)
		{
			if(codeError == Exception::EMemAllocError)
			{
				std::cout << "|.then got exception: memory allocation error"<<std::endl;
			}
			if(codeError == Exception::EIndexOutOfRange)
			{
				std::cout << "|.then got exception: out of range"<<std::endl;
			}
			status = "Test Erase failed";
		}
		std::cout << status << std::endl;
    }
    //-----------------------------------
    //! @brief Testing clearing
    //-----------------------------------
    void TestClear()
    {
        std::string status = "Test Clear passed";
        try
        {
            std::cout << "|.Given array with values (0.." << defaultSize-1 << ")" << std::endl;
            std::cout << "|.When inserted "<<defaultSize<<" elements and clear" << std::endl;
            Array<Type>* testobj = new Array<Type>(defaultSize);
            for (int i = 0; i < defaultSize; i++)
            {
                (*testobj)[i] = static_cast<Type>(i);
            }
            testobj->Clear();
            std::cout << "|.then expected that elements will be 0" <<std::endl;
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
                std::cout << "|.then got exception: memory allocation error"<<std::endl;
            }
            if(codeError == Exception::EIndexOutOfRange)
            {
                std::cout << "|.then got exception: out of range"<<std::endl;
            }
            status = "Test Clear failed";
        }
        std::cout << status << std::endl;
    }
    //-----------------------------------
    //! @brief Testing changing size of Array with border-case
    //-----------------------------------
    void TestResize()
	{
		std::string status = "Test Resize passed";
		try
		{
			std::cout << "|.Given array with size 0" << std::endl;

			Array<Type>* testobj = new Array<Type>;
			std::cout << "|.When resized from 0 to " << defaultSize <<std::endl;
			testobj->Resize(defaultSize);
			for (int i = 0; i < defaultSize; i++)
			{
				(*testobj)[i] = static_cast<Type>(i);
			}
			std::cout << "|.then excepted that in index = "<<defaultSize - 1 << " will be " << static_cast<Type>(defaultSize-1)<<std::endl;
			std::cout << "|.and got " << (*testobj)[defaultSize - 1] <<std::endl;
			if ( (*testobj)[defaultSize - 1] != static_cast<Type>(defaultSize - 1) || testobj->Size() != defaultSize)
			{
				throw Exception::ETestFailed;
			}
			testobj->Resize(1);
			std::cout <<"|.When resized from "<<defaultSize << " to 1" <<std::endl;
			std::cout << "|.then excepted that in index = 0 will be " << static_cast<Type>(0) << std::endl;
			std::cout << "|.and got " << (*testobj)[0];
			if ( (*testobj)[0] != static_cast<Type>(0) || testobj->Size() != 1)
			{
				throw Exception::ETestFailed;
			}
		}
		catch(int codeError)
		{
			if(codeError == Exception::EMemAllocError)
			{
				std::cout << "|.then got exception: memory allocation error"<<std::endl;
			}
			if(codeError == Exception::EIndexOutOfRange)
			{
				std::cout << "|.then got exception: out of range"<<std::endl;
			}
			if(codeError == Exception::EBadSize)
			{
				std::cout << "|.then got exception: badsize in argument"<<std::endl;
			}
			status = "Test Resize failed";
		}
		std::cout << status << std::endl;
	}
    //-----------------------------------
    //! @brief Testing operator << and correction of Dump
    //-----------------------------------
    void TestDump()
    {
        std::string status = "Test Dump passed";
        std::cout << "Given array with values (0..10)" << std::endl;
        Array<Type>* testobj = new Array<Type>(10);
        for (int i=0; i<10; i++)
        {
            (*testobj)[i] = static_cast<Type>(i);
        }
        std::cout << "When dumping it" << std::endl;
        try
        {
        testobj->Dump();
        std::cout << "then get the dump" << std::endl;
        }
        catch (int errorCode)
        {
            if (errorCode == Exception::EFileCreationError)
                std::cout << "then get file creation error" << std::endl;

            status = "Test Dump failed";
        }
        std::cout << status << std::endl;
    }


	void TestInit()
	{
		    std::string status = "Test Init passed";
			std::cout << "Given array with values " << std::endl;

		try
		{
			Array<int> test(10);
			new(&test,0) Array<int>(test);
			for (int i = 0; i < 10; i++)
			{
				if (test[i] != 0)
					throw Exception::ETestFailed;
			}
		}
		catch (int errorCode)
		{
			status = "Test Init failed";
		}
		std::cout << "\n" << status << std::endl;

	}

};



#endif // ARRAYTEST_H
