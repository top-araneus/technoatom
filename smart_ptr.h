#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <cstdlib>

template <typename Type>
class Auto_ptr
{
public:
	Auto_ptr();
	~Auto_ptr();
	Auto_ptr(Auto_ptr& that);
	Auto_ptr(Type* pObject);
	Auto_ptr& operator=(Auto_ptr& that);
	Type& operator*();
	Type* operator->();
protected:
	Type* ptr_;
};

template <typename Type>
Auto_ptr<Type>::Auto_ptr()
{
	ptr_ = nullptr;
}

template <typename Type>
Auto_ptr<Type>::~Auto_ptr()
{
	delete ptr_;
}

template <typename Type>
Auto_ptr<Type>::Auto_ptr(Auto_ptr& that)
{
	ptr_ = nullptr;
	std::swap(ptr_, that.ptr_);
}

template <typename Type>
Auto_ptr<Type>::Auto_ptr(Type *pObject)
{
	ptr_ = pObject;
}

template <typename Type>
Auto_ptr<Type>& Auto_ptr<Type>::operator=(Auto_ptr& that)
{
	delete ptr_;
	ptr_ = nullptr;
	std::swap(this->ptr_, that.ptr_);
}

template <typename Type>
Type& Auto_ptr<Type>::operator*()
{
	return(*ptr_);
}

template <typename Type>
Type* Auto_ptr<Type>::operator->()
{
	return(ptr_);
}

template <typename Type>
class Unique_ptr : public Auto_ptr
{
	Unique_ptr();
	~Unique_ptr();
	Unique_ptr(Type* pObject);
	Unique_ptr(Unique_ptr& that) = delete;
	Unique_ptr& operator=(Unique_ptr& that) = delete;
	Unique_ptr(Unique_ptr&& that);
	Unique_ptr& operator=(Unique_ptr&& that);
};

template <typename Type>
Unique_ptr::Unique_ptr()
{
	ptr_ = nullptr;
}

template <typename Type>
Unique_ptr::~Unique_ptr()
{
	delete ptr_;
}

template <typename Type>
Unique_ptr::Unique_ptr(Type *pObject)
{
	ptr_ = pObject;
}

template <typename Type>
Unique_ptr::Unique_ptr(Unique_ptr&& that)
{
	std::swap(this->ptr_, that.ptr_);
}

template <typename Type>
Unique_ptr& Unique_ptr::operator=(Unique_ptr&& that)
{
	std::swap(this->ptr_, that.ptr_);
}

template <typename Type>
class SharedProxy
{
private:
	Type* pObject_;
	size_t NumofRef_;
public:
	SharedProxy(Type* pObject);
	~SharedProxy();
	SharedProxy& operator++();
};

template <typename Type>
SharedProxy::SharedProxy(Type *pObject)
{
	pObject_ = pObject;
	NumofRef_ = 1;
}

template <typename Type>
SharedProxy::~SharedProxy(Type *pObject)
{
	if (NumofRef_ == 1)
	{
		delete pObject_;
	}
	else
	{
		NumofRef_--;
	}
}

template <typename Type>
SharedProxy& SharedProxy::operator ++()
{
	NumofRef_++;
	return *this;
}

#endif // SMART_PTR_H
