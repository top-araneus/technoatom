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
class Unique_ptr : public Auto_ptr<Type>
{
    public:
        Unique_ptr();
        ~Unique_ptr();
        Unique_ptr(Type* pObject);
        Unique_ptr(Unique_ptr& that) = delete;
        Unique_ptr& operator=(Unique_ptr& that) = delete;
        Unique_ptr(Unique_ptr&& that);
        Unique_ptr& operator=(Unique_ptr&& that);
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
}

template <typename Type>
class Shared_ptr
{
public:
    Shared_ptr();
    ~Shared_ptr();
    Shared_ptr(Type* pObject);
    Shared_ptr(Shared_ptr& that);
    Shared_ptr(Shared_ptr&& that);
    Shared_ptr& operator=(Shared_ptr& that);
    Shared_ptr& operator=(Shared_ptr&& that);
    Type& operator*();
    Type* operator->();
private:
    class SharedProxy
    {
    private:
        Type* pObject_;
        size_t NumofRef_;
    public:
        SharedProxy(Type *pObject)
        {
            pObject_ = pObject;
            NumofRef_ = 1;
        }

        ~SharedProxy()
        {
            if (NumofRef_ == 1)
            {
                delete pObject_;
                pObject_ = nullptr;
            }
            else
            {
                NumofRef_--;
            }
        }

        SharedProxy& operator ++()
        {
            NumofRef_++;
            return *this;
        }
    };

    SharedProxy* proxy_;
};

template <typename Type>
Shared_ptr<Type>::Shared_ptr()
{
    proxy_ = nullptr;
}

template <typename Type>
Shared_ptr<Type>::~Shared_ptr()
{
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
    ++(*proxy_);
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
    delete proxy_;
    proxy_ = that.proxy_;
    ++(*proxy_);
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
    return *(proxy_->pObject_);
}

template <typename Type>
Type* Shared_ptr<Type>::operator->()
{
    return proxy_->pObject_;
}


#endif // SMART_PTR_H
