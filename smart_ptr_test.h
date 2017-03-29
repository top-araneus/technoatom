//-----------------------------------
//! @file smart_ptr_test.h
//! Unit tests for custom smart pointers
//!
//! team araneus, 2017
//-----------------------------------
#ifndef SMART_PTR_TEST_H
#define SMART_PTR_TEST_H
#include "smart_ptr.h"
#include "array.h"

//-----------------------------------
//! @brief Tests for auto_ptr.
//! Contains assignment, copy and arrow tests.
//-----------------------------------
template <typename Type>
class Test_auto_ptr
{
public:
    static const int TEST_VALUE = 10;

    void TestAll()
    {
        print("Starting tests for Auto_ptr \n");
        Assignment();
        Copy();
        Arrow();
        print("Tests finished. \n\n");
    }

    //-----------------------------------
    //! @fn Assignment()
    //! @brief Test for dereferencing and assignment between auto_ptrs
    //-----------------------------------
	void Assignment()
	{
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Auto_ptr<Type> p1_auto(new Type);
			Auto_ptr<Type> p2_auto(new Type);
			*p1_auto = TEST_VALUE;
			//when
			p2_auto = p1_auto;
			//then
			if(*p2_auto != static_cast<Type>(TEST_VALUE))
			{
				throw EXCEPT(Exception::ETestFailed, "Wrong assignment", nullptr);
			}
			*p1_auto;
		}
		catch(Exception err)
		{
			if(err.errcode_ != Exception::ENullDereference)
				std::cout << err;
		}
	}

    //-----------------------------------
    //! @fn Copy()
    //! @brief Test for auto_ptr's copy constructor
    //-----------------------------------
	void Copy()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Auto_ptr<Type> p1_auto(new Type);
			*p1_auto = TEST_VALUE;
			//when
			Auto_ptr<Type> p2_auto(p1_auto);
			//then
			if(*p2_auto != static_cast<Type>(TEST_VALUE))
			{
				throw EXCEPT(Exception::ETestFailed, "Wrong assignment", nullptr);
			}
			*p1_auto;
		}
		catch(Exception err)
		{
			if(err.errcode_ != Exception::ENullDereference)
				std::cout << err;
		}
	}

    //-----------------------------------
    //! @fn Arrow()
    //! @brief Test for operator ->,
    //! using auto_ptr as simple pointer to object
    //-----------------------------------
	void Arrow()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Auto_ptr<Array<Type>> p_auto(new Array<Type>);
			//when
			p_auto->PushBack(static_cast<Type>(TEST_VALUE));
			//then
			if((*p_auto)[0] != static_cast<Type>(TEST_VALUE))
			{
				throw EXCEPT(Exception::ETestFailed, " incorrect value", nullptr);
			}
		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}

};

//-----------------------------------
//! @brief Tests for unique_ptr.
//! Contains move assignment, move constructor and arrow tests.
//-----------------------------------
template <typename Type>
class Test_unique_ptr
{
public:
    static const int TEST_VALUE = 10;

    void TestAll()
    {
        print("Starting tests for Unique_ptr \n");
        MoveAssignment();
        MoveCopy();
        Arrow();
        print("Tests finished. \n\n");
    }

    //-----------------------------------
    //! @fn MoveAssignment()
    //! @brief Test for assignment temporary object to unique_ptr
    //-----------------------------------
	void MoveAssignment()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Unique_ptr<Type> p1_unique;
			Type* obj = new Type;
			*obj = static_cast<Type>(TEST_VALUE);
			//when
			 p1_unique = Unique_ptr<Type>(obj);
			//then
			if(*p1_unique != static_cast<Type>(TEST_VALUE))
			{
				throw EXCEPT(Exception::ETestFailed, "Wrong assignment", nullptr);
			}
		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}
    //-----------------------------------
    //! @fn MoveCopy()
    //! @brief Test for initializing unique_ptr by temporary object
    //-----------------------------------
	void MoveCopy()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Type* obj = new Type;
			*obj = static_cast<Type>(TEST_VALUE);
			//when
			 Unique_ptr<Type> p1_unique = Unique_ptr<Type>(obj);
			//then
			if(*p1_unique != static_cast<Type>(TEST_VALUE) || *obj != static_cast<Type>(TEST_VALUE))
			{
				throw EXCEPT(Exception::ETestFailed, "Wrong assignment", nullptr);
			}
		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}
    //-----------------------------------
    //! @fn Arrow()
    //! @brief Test for operator ->,
    //! using unique_ptr as simple pointer to object
    //-----------------------------------
	void Arrow()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Unique_ptr<Array<Type>> p_auto(new Array<Type>);
			//when
			p_auto->PushBack(static_cast<Type>(TEST_VALUE));
			//then
			if((*p_auto)[0] != static_cast<Type>(TEST_VALUE))
			{
				throw EXCEPT(Exception::ETestFailed, " incorrect value", nullptr);
			}
		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}

};

//-----------------------------------
//! @brief Tests for shared_ptr
//! Contains assignment, copy, arrow tests,
//! and tests for operations with proxy.
//-----------------------------------
template <typename Type>
class Test_shared_ptr
{
public:

	static const int TEST_VALUE = 10;
	static const int TEST_VALUE_2 = 100;

    void TestAll()
    {
        print("Starting tests for Shared_ptr \n");
        Assignment();
        Copy();
        Arrow();
        CountIncrease();
        CountDecreaseDelete();
        CountDecreaseAssignment();
        CountMove();
        print("Tests finished. \n\n");
    }
    //-----------------------------------
    //! @fn Assignment()
    //! @brief Test for dereferencing and assignment between shared_ptrs
    //-----------------------------------
	void Assignment()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
            Shared_ptr<Type> p1_shared(new Type);
            Shared_ptr<Type> p2_shared(new Type);
            *p1_shared = TEST_VALUE;
			//when
            p2_shared = p1_shared;
			//then
            if(*p1_shared != static_cast<Type>(TEST_VALUE) || *p2_shared != static_cast<Type>(TEST_VALUE) )
			{
				throw EXCEPT(Exception::ETestFailed, "Wrong assignment", nullptr);
			}

		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}
    //-----------------------------------
    //! @fn Copy()
    //! @brief Test for shared_ptr's copy constructor
    //-----------------------------------
	void Copy()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Shared_ptr<Type> p1_shared(new Type);
			*p1_shared = TEST_VALUE;
			//when
			Shared_ptr<Type> p2_shared(p1_shared);
			//then
			if(*p1_shared != static_cast<Type>(TEST_VALUE) || *p2_shared != static_cast<Type>(TEST_VALUE))
			{
				throw EXCEPT(Exception::ETestFailed, "Wrong assignment", nullptr);
			}
		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}
    //-----------------------------------
    //! @fn Arrow()
    //! @brief Test for operator ->,
    //! using shared_ptr as simple pointer to object
    //-----------------------------------
	void Arrow()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Unique_ptr<Array<Type>> p_shared(new Array<Type>);
			//when
			p_shared->PushBack(static_cast<Type>(TEST_VALUE));
			//then
			if((*p_shared)[0] != static_cast<Type>(TEST_VALUE))
			{
				throw EXCEPT(Exception::ETestFailed, " incorrect value", nullptr);
			}
		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}
    //-----------------------------------
    //! @fn CountIncrease()
    //! @brief Test for proxy and increasing number of links
    //! if permanent shared_ptr was initialized by existing shared_ptr
    //-----------------------------------
	void CountIncrease()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Shared_ptr<Type> p1_shared(new Type);
			*p1_shared = static_cast<Type>(TEST_VALUE);
			//when
			Shared_ptr<Type> p2_shared = p1_shared;
			//then
			if(p2_shared.GetCount() != 2)
			{
				throw EXCEPT(Exception::ETestFailed, "count not increase", nullptr);
			}
		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}
    //-----------------------------------
    //! @fn CountDecreaseDelete()
    //! @brief Test for proxy and decreasing number of links
    //! when connected with proxy object was deleted
    //-----------------------------------
	void CountDecreaseDelete()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Shared_ptr<Type> p1_shared(new Type);
			*p1_shared = static_cast<Type>(TEST_VALUE);
			//when
			Shared_ptr<Type> p2_shared = p1_shared;
			delete &p1_shared;
			//then
			if(p2_shared.GetCount() != 1 || *p2_shared != static_cast<Type>(TEST_VALUE) )
			{
				throw EXCEPT(Exception::ETestFailed, "count not decrease", nullptr);
			}

		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}
    //-----------------------------------
    //! @fn CountDecreaseAssignment()
    //! @brief Test for proxy and decreasing number of links
    //! when connected with proxy object was reassigned
    //-----------------------------------
	void CountDecreaseAssignment()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Shared_ptr<Type> p1_shared(new Type);
			*p1_shared = static_cast<Type>(TEST_VALUE);
			Shared_ptr<Type> p2_shared = p1_shared;
			Shared_ptr<Type> p3_shared(new Type);
			*p3_shared = static_cast<Type>(TEST_VALUE_2);
			//when
			p2_shared = p3_shared;
			//then
			if(p1_shared.GetCount() != 1 || p3_shared.GetCount() != 2)
			{
				throw EXCEPT(Exception::ETestFailed, "count not decrease", nullptr);
			}

		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}
    //-----------------------------------
    //! @fn CountDecreaseAssignment()
    //! @brief Test for proxy: count of references
    //! mustn't change if rvalue object was initialized with same proxy
    //-----------------------------------
	void CountMove()
    {
        print("/# \n", __PRETTY_FUNCTION__);
		try
		{
			//given
			Shared_ptr<Type> p1_shared(new Type);
			*p1_shared = TEST_VALUE;
			Shared_ptr<Type> p2_shared = p1_shared;
			Type* obj = new Type;
			*obj = TEST_VALUE_2;
			//when
			p2_shared = Shared_ptr<Type>(obj);
			//then
			if(p1_shared.GetCount() != 1 || *p2_shared != TEST_VALUE_2)
			{
				throw EXCEPT(Exception::ETestFailed, "move works incorrect", nullptr);
			}
		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}

};

#endif // SMART_PTR_TEST_H
