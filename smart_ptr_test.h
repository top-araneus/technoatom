#ifndef SMART_PTR_TEST_H
#define SMART_PTR_TEST_H
#include "smart_ptr.h"
#include "array.h"

template <typename Type>
class Test_auto_ptr
{
public:
	static const int TEST_VALUE = 10;
	void Assignment()
	{
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

	void Copy()
	{
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

	void Arrow()
	{
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

template <typename Type>
class Test_unique_ptr
{
public:
	static const int TEST_VALUE = 10;
	void Assignment()
	{
		try
		{
			//given
			Unique_ptr<Type> p1_unique(new Type);
			Unique_ptr<Type> p2_unique(new Type);
			*p1_unique = TEST_VALUE;
			//when
			//		p2_unique = p1_unique;
			//then
			if(*p2_unique != TEST_VALUE)
			{
				throw EXCEPT(Exception::ETestFailed, "Wrong assignment", nullptr);
			}
			*p1_unique;
		}
		catch(Exception err)
		{
			if(err.errcode_ != Exception::ENullDereference)
				std::cout << err;
		}
	}
	void MoveAssignment()
	{
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

	void MoveCopy()
	{
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

	void Arrow()
	{
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

template <typename Type>
class Test_shared_ptr
{
public:

	static const int TEST_VALUE = 10;
	static const int TEST_VALUE_2 = 100;

	void Assignment()
	{
		try
		{
			//given
			Shared_ptr<Type> p1_auto(new Type);
			Shared_ptr<Type> p2_auto(new Type);
			*p1_auto = TEST_VALUE;
			//when
			p2_auto = p1_auto;
			//then
			if(*p1_auto != static_cast<Type>(TEST_VALUE) || *p2_auto != static_cast<Type>(TEST_VALUE) )
			{
				throw EXCEPT(Exception::ETestFailed, "Wrong assignment", nullptr);
			}

		}
		catch(Exception err)
		{
			std::cout << err;
		}
	}

	void Copy()
	{
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

	void Arrow()
	{
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

	void CountIncrease()
	{
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

	void CountDecreaseDelete()
	{
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
	void CountDecreaseAssignment()
	{
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

	void CountMove()
	{
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
