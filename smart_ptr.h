//-----------------------------------
//! @file smart_ptr.h
//! Implements custom Auto_ptr, Unique_ptr and Smart_ptr classes.
//!
//! team araneus, 2017
//-----------------------------------
#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <cstdlib>
#include "exception.h"
//-----------------------------------
//! @brief Auto_ptr class. Type is a type of element auto_ptr references to.
//! Auto_ptr works as pointer, but copy and assignment works
//! as moving object to another address.
//-----------------------------------
template <typename Type>
class Auto_ptr
{
public:
	Auto_ptr();
    ~Auto_ptr();

    //-----------------------------------
    //! @fn Auto_ptr(Auto_ptr& that)
    //! @brief "Copy" (moving) constructor for auto_ptr
    //! @arg Auto_ptr& that is a pointer that will be moved to this auto_ptr
    //-----------------------------------
	Auto_ptr(Auto_ptr& that);

    //-----------------------------------
    //! @fn Auto_ptr(Type* pObject)
    //! @brief Initializing constructor
    //! @arg Type* pObject is a pointer that will be saved to this auto_ptr
    //-----------------------------------
    Auto_ptr(Type* pObject);

    //-----------------------------------
    //! @fn Auto_ptr& operator=(Auto_ptr& that)
    //! @brief "Copy" (moving) operator
    //! @arg Auto_ptr& that is a pointer that will be moved to this auto_ptr
    //! @return this auto_ptr
    //-----------------------------------
	Auto_ptr& operator=(Auto_ptr& that);

    //-----------------------------------
    //! @fn Type& operator*()
    //! @brief Depointing operator
    //! @return reference to value of object
    //-----------------------------------
	Type& operator*();

    //-----------------------------------
    //! @fn Type& operator->()
    //! @brief operator for access to fields of object inside
    //! @return simple pointer to object
    //-----------------------------------
    Type* operator->();

    //-----------------------------------
    //! @fn bool IsEmpty()
    //! @return true if pointer is null
    //-----------------------------------
	bool IsEmpty();

    //-----------------------------------
    //! @fn operator Auto_ptr<Convertion_Type>()
    //! @brief operator for using pointer as a pointer of another type
    //-----------------------------------
	template <typename Convertion_Type>
	    operator Auto_ptr<Convertion_Type>();

private:
    Type* ptr_; //!< Type* ptr_ is a simple pointer that is contained in auto_ptr
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
    if (this != &that)
    {
        delete ptr_;
        ptr_ = nullptr;
        std::swap(this->ptr_, that.ptr_);
    }
    return *this;
}

template <typename Type>
Type& Auto_ptr<Type>::operator*()
{
	if (IsEmpty())
	{
		throw Exception(Exception::ENullDereference, "Try to dereference nullptr", __FILE__, __LINE__, nullptr);
	}
	return(*ptr_);
}

template <typename Type>
Type* Auto_ptr<Type>::operator->()
{
	if (IsEmpty())
	{
		throw Exception(Exception::ENullDereference, "Try to dereference nullptr", __FILE__, __LINE__, nullptr);
	}
	return(ptr_);
}

template <typename Type>
bool Auto_ptr<Type>::IsEmpty()
{
	return !ptr_;
}

template <typename Type>
template <typename Convertion_Type>
Auto_ptr<Type>::operator Auto_ptr<Convertion_Type>()
{
   return Auto_ptr<Convertion_Type>((Convertion_Type*)ptr_);
}

//-----------------------------------
//! @brief Unique_ptr class. Type is a type of element unique_ptr references to.
//! Unique_ptr works as pointer, but copy and assignment are forbidden for permanent objects.
//-----------------------------------
template <typename Type>
class Unique_ptr
{
    public:
        Unique_ptr();
        ~Unique_ptr();

        //-----------------------------------
        //! @fn Unique_ptr(Type* pObject)
        //! @brief Initializing constructor
        //! @arg Type* pObject is a pointer that will be saved to this Unique_ptr
        //-----------------------------------
        Unique_ptr(Type* pObject);

        //!< Copy semantics is forbidden for Unique_ptr
        Unique_ptr(Unique_ptr& that) = delete;
        Unique_ptr& operator=(Unique_ptr& that) = delete;

        //-----------------------------------
        //! @fn Unique_ptr(Unique_ptr&& that)
        //! @brief Moving constructor for Unique_ptr
        //! @arg Unique_ptr&& that is a pointer to temporary object
        //! that will be moved to this unique_ptr
        //-----------------------------------
        Unique_ptr(Unique_ptr&& that);

        //-----------------------------------
        //! @fn Unique_ptr& operator=(Unique_ptr&& that)
        //! @brief Moving assignment operator
        //! @arg Unique_ptr&& that is a pointer to temporary object
        //! that will be moved to this Unique_ptr
        //! @return this Unique_ptr
        //-----------------------------------
        Unique_ptr& operator=(Unique_ptr&& that);

        //-----------------------------------
        //! @fn Type& operator*()
        //! @brief Depointing operator
        //! @return reference to value of object
        //-----------------------------------
        Type& operator*();

        //-----------------------------------
        //! @fn Type& operator->()
        //! @brief operator for access to fields of object inside
        //! @return simple pointer to object
        //-----------------------------------
        Type* operator->();

        //-----------------------------------
        //! @fn bool IsEmpty()
        //! @return true if pointer is null
        //-----------------------------------
        bool IsEmpty();

        //-----------------------------------
        //! @fn operator Unique_ptr<Convertion_Type>()
        //! @brief operator for using pointer as a pointer of another type
        //-----------------------------------
        template <typename Convertion_Type>
            operator Unique_ptr<Convertion_Type>();
private:
    Type* ptr_; //!< Type* ptr_ is a simple pointer that is contained in Unique_ptr
};

template <typename Type>
Unique_ptr<Type>::Unique_ptr()
{
    this->ptr_ = nullptr;
}

template <typename Type>
Unique_ptr<Type>::~Unique_ptr()
{
    delete this->ptr_;
}

template <typename Type>
Unique_ptr<Type>::Unique_ptr(Type *pObject)
{
    this->ptr_ = pObject;
}

template <typename Type>
Unique_ptr<Type>::Unique_ptr(Unique_ptr&& that)
{
	std::swap(this->ptr_, that.ptr_);
}

template <typename Type>
Unique_ptr<Type>& Unique_ptr<Type>::operator=(Unique_ptr&& that)
{
	std::swap(this->ptr_, that.ptr_);
    return *this;
}

template <typename Type>
Type& Unique_ptr<Type>::operator*()
{
    if (IsEmpty())
    {
        throw Exception(Exception::ENullDereference, "Try to dereference nullptr", __FILE__, __LINE__, nullptr);
    }
    return(*ptr_);
}

template <typename Type>
Type* Unique_ptr<Type>::operator->()
{
    if (IsEmpty())
    {
        throw Exception(Exception::ENullDereference, "Try to dereference nullptr", __FILE__, __LINE__, nullptr);
    }
    return(ptr_);
}

template <typename Type>
bool Unique_ptr<Type>::IsEmpty()
{
    return !ptr_;
}

template <typename Type>
template <typename Convertion_Type>
Unique_ptr<Type>::operator Unique_ptr<Convertion_Type>()
{
   return Unique_ptr<Convertion_Type>((Convertion_Type*)ptr_);
}

//-----------------------------------
//! @brief Shared_ptr class. Type is a type of element Shared_ptr references to.
//! Shared_ptr works as pointer, but uses proxy for solving property problem.
//-----------------------------------
template <typename Type>
class Shared_ptr
{
public:
    Shared_ptr();
    ~Shared_ptr();

    //-----------------------------------
    //! @fn Shared_ptr(Type* pObject)
    //! @brief Initializing constructor
    //! @arg Type* pObject is a pointer that will be saved to this Shared_ptr
    //-----------------------------------
    Shared_ptr(Type* pObject);

    //-----------------------------------
    //! @fn Shared_ptr(Shared_ptr& that)
    //! @brief Copy constructor for Shared_ptr
    //! @arg Shared_ptr& that is a pointer to object
    //! that will be copied to this Shared_ptr
    //-----------------------------------
    Shared_ptr(Shared_ptr& that);

    //-----------------------------------
    //! @fn Shared_ptr(Shared_ptr&& that)
    //! @brief Moving constructor for Shared_ptr
    //! @arg Shared_ptr&& that is a pointer to temporary object
    //! that will be moved to this Shared_ptr
    //-----------------------------------
    Shared_ptr(Shared_ptr&& that);

    //-----------------------------------
    //! @fn Shared_ptr& operator=(Shared_ptr&& that)
    //! @brief Copy assignment operator
    //! @arg Shared_ptr& that is a pointer to object
    //! that will be copied to this Shared_ptr
    //! @return this Shared_ptr
    //-----------------------------------
    Shared_ptr& operator=(Shared_ptr& that);

    //-----------------------------------
    //! @fn Shared_ptr& operator=(Shared_ptr&& that)
    //! @brief Moving assignment operator
    //! @arg Shared_ptr&& that is a pointer to temporary object
    //! that will be moved to this Shared_ptr
    //! @return this Shared_ptr
    //-----------------------------------
    Shared_ptr& operator=(Shared_ptr&& that);

    //-----------------------------------
    //! @fn size_t GetCount()
    //! @return number of references from proxy shared_ptr is connected with
    //-----------------------------------
	size_t GetCount();

    //-----------------------------------
    //! @fn Type& operator*()
    //! @brief Depointing operator
    //! @return reference to value of object
    //-----------------------------------
    Type& operator*();

    //-----------------------------------
    //! @fn Type& operator->()
    //! @brief operator for access to fields of object inside
    //! @return simple pointer to object
    //-----------------------------------
    Type* operator->();

    //-----------------------------------
    //! @fn bool IsEmpty()
    //! @return true if ptr is null
    //-----------------------------------
	bool IsEmpty();

    //-----------------------------------
    //! @fn operator Shared_ptr<Convertion_Type>()
    //! @brief operator for using pointer as a pointer of another type
    //-----------------------------------
    template <typename Convertion_Type>
        operator Shared_ptr<Convertion_Type>();

private:
    //-----------------------------------
    //! @brief SharedProxy class. It's a counter for objects that contains pointers to address pObject_.
    //-----------------------------------
    class SharedProxy
    {
    private:
        Type* pObject_;
        size_t NumofRef_;
    public:

        //-----------------------------------
        //! @fn SharedProxy(Type* pObject)
        //! @brief Initializing constructor
        //! @arg Type* pObject is a pointer that will be saved to this SharedProxy
        //-----------------------------------
        SharedProxy(Type *pObject)
        {
            pObject_ = pObject;
            NumofRef_ = 1;
        }

        ~SharedProxy()
        {
            NumofRef_ = 0;
            delete pObject_;
        }

        //-----------------------------------
        //! @fn void Increase()
        //! @brief Increases number of references.
        //-----------------------------------
        void Increase()
        {
            NumofRef_++;
        }

        //-----------------------------------
        //! @fn void Decrease()
        //! @brief Decreases number of references.
        //-----------------------------------
        void Decrease()
        {
            NumofRef_--;
        }

        //-----------------------------------
        //! @fn Type* GetPointer()
        //! @return internal pointer to object
        //-----------------------------------
		Type* GetPointer()
		{
			return pObject_;
		}

        //-----------------------------------
        //! @fn size_t GetCount()
        //! @return number of references
        //-----------------------------------
		size_t GetCount()
		{
			return NumofRef_;
		}
    };

    SharedProxy* proxy_; //!< SharedProxy* proxy_ is a proxy for this shared_ptr
};

template <typename Type>
Shared_ptr<Type>::Shared_ptr()
{
    proxy_ = new SharedProxy(nullptr);
}

template <typename Type>
Shared_ptr<Type>::~Shared_ptr()
{
    if (proxy_->GetCount() > 1)
        proxy_->Decrease();
    else
        delete proxy_;
}


template <typename Type>
Shared_ptr<Type>::Shared_ptr(Type* pObject)
{
    proxy_ = new SharedProxy(pObject);
}

template <typename Type>
Shared_ptr<Type>::Shared_ptr(Shared_ptr<Type> &that)
{
    proxy_ = that.proxy_;
    proxy_->Increase();
}

template <typename Type>
Shared_ptr<Type>::Shared_ptr(Shared_ptr<Type>&& that)
{
    proxy_ = nullptr;
    std::swap(proxy_, that.proxy_);
}

template <typename Type>
Shared_ptr<Type>& Shared_ptr<Type>::operator=(Shared_ptr<Type>& that)
{
    if (this != &that)
    {
        if (proxy_->GetCount() > 1)
            proxy_->Decrease();
        else
            delete proxy_;
        proxy_ = that.proxy_;
        proxy_->Increase();
    }
    return *this;
}

template <typename Type>
Shared_ptr<Type>& Shared_ptr<Type>::operator=(Shared_ptr<Type>&& that)
{
    std::swap(proxy_, that.proxy_);
    return *this;
}

template <typename Type>
Type& Shared_ptr<Type>::operator*()
{
	if (IsEmpty())
	{
		throw Exception(Exception::ENullDereference, "Try to dereference nullptr", __FILE__, __LINE__, nullptr);
	}
	return *(proxy_->GetPointer());
}

template <typename Type>
Type* Shared_ptr<Type>::operator->()
{
	if (IsEmpty())
	{
		throw Exception(Exception::ENullDereference, "Try to dereference nullptr", __FILE__, __LINE__, nullptr);
	}
    return proxy_->pObject_;
}

template <typename Type>
bool Shared_ptr<Type>::IsEmpty()
{
    return !(proxy_->GetPointer());
}

template <typename Type>
size_t Shared_ptr<Type>::GetCount()
{
	return proxy_->GetCount();
}

template <typename Type>
template <typename Convertion_Type>
Shared_ptr<Type>::operator Shared_ptr<Convertion_Type>()
{
   return Shared_ptr<Convertion_Type>((Convertion_Type*)(proxy_->GetPointer()));
}
#endif // SMART_PTR_H
