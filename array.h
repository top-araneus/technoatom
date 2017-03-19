//-----------------------------------
//! @file array.h
//! Implements array class
//!
//! team araneus, 2017
//-----------------------------------
#ifndef ARRAY_H
#define ARRAY_H
#include <ctime>
#include <typeinfo>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;

//-----------------------------------
//! @brief Array class. Type is a type of elements array stores.
//-----------------------------------

template <typename Type>
class Array
{
private:
    //-----------------------------------
    //! @fn Copy()
    //! @brief Creates copy of container from args in range of
    //! provided indexes (including them).
    //! @arg Type * that is container user wants to copy from
    //! @arg int first is index from which copying started
    //! @arg int last is index on which copying finished
    //! @return Type *: pointer to container with copied elements
    //-----------------------------------
    inline Type *Copy(const Type *that, int first, int last);

    //-----------------------------------
    //! @fn Concat()
    //! @brief Creates concatenated container from two others
    //! @arg Type * left is container which stores left elements
    //! @arg Type * right is container which stores right elements
    //! @arg size_t leftLen is capacity of left container
    //! @arg size_t rightLen is capacity of right container
    //! @return Type *: pointer to concatenated container
    //-----------------------------------
    inline Type *Concat(const Type *left, const Type *right, size_t leftLen, size_t rightLen) const;
    //-----------------------------------

    //-----------------------------------
    inline Type *Concat(const Type *left,const Type *right, size_t leftLen) const;

    //-----------------------------------
    //! @var int size is a capacity of array
    //-----------------------------------
    int size_;

    //-----------------------------------
    //! @var Type * data is a container with elements
    //-----------------------------------

    Type* data_;


    //-----------------------------------
    //! @brief static const size_t POISON_INT
    //! is a poison value to fill garbage objects
    //-----------------------------------
    static const size_t POISON_INT = 0xBADA55;
public:

    Array();
    //-----------------------------------
    //! @fn Array(int size)
    //! @brief Constructs array with defined size
    //! @arg int size is a number of elements array can store
    //-----------------------------------
    Array(const int size);

    void* operator new(size_t size) throw (std::bad_alloc)
    {
        return ::new Type(size);
    }

    //-----------------------------------
    //! @fn operator new(size_t size, void* ptr)
    //! @brief placement new
    //! @arg size_t size is a default arg which contains size of type
    //! @arg void* ptr is an address where object will be created
    //! @return void* address where object was created (equals to ptr)
    //-----------------------------------
    void* operator new(size_t size, void* ptr) throw (std::bad_alloc)
    {
        return ptr;
    }

    //-----------------------------------
    //! @fn operator new(size_t size, void* ptr, int num)
    //! @brief initializing placement new.
    //! When placement new should be called, there should be called
    //! a copy constructor with reference to this Array in argument
    //! @example new(&example,0) Array<int>(example); //example is Array user wants to initialize
    //! @arg size_t size is a default arg which contains size of type
    //! @arg void* ptr is an address where object will be created
    //! @arg int num is an initialization key
    //! @return void* address where object was created (equals to ptr)
    //-----------------------------------
    void* operator new(size_t size, void* ptr, int num)
    {
        Array<Type> *bufptr = (Array<Type>*)ptr;
        std::memset(bufptr->data_, num, sizeof(Type)*bufptr->size_);
        return ptr;
    }

    //-----------------------------------
    //! @fn Array(const Array&& that)
    //! @brief Moving constructor
    //! @arg Array&& that is a r-value reference to temporary object
    //-----------------------------------
    Array(Array&& that);

    //-----------------------------------
    //! @fn Array(const Array& that)
    //! @brief Copy constructor
    //! @arg Array& that is a link to array user wants to copy from
    //-----------------------------------
    Array(Array& that);

    //-----------------------------------
    //! @fn Array(std::initializer_list lst)
    //! @brief initialization constructor
    //-----------------------------------
    Array(const std::initializer_list<Type>& lst);

    ~Array();
    //-----------------------------------
    //! @fn Resize()
    //! @brief Changes capacity of array (how many elements can it store).
    //! Deletes last elements if new size is less than old size.
    //! @arg int newsize is new capacity of array
    //-----------------------------------
    void Resize(int newsize);

    //-----------------------------------
    //! @fn Insert()
    //! @brief Inserts element to the array, translocating right elements
    //! @arg int index is a future index of element in array
    //! @arg Type element is an element user wants to insert
    //-----------------------------------
    void Insert(int index,Type element);

    //-----------------------------------
    //! @fn Erase()
    //! @brief Removes element from array, translocating right elements
    //! @arg int index is index of the element that will be deleted
    //-----------------------------------
    void Erase(int index);

    //-----------------------------------
    //! @fn Clear()
    //! @brief Removes all elements from array with saving size.
    //-----------------------------------
    void Clear();

    //-----------------------------------
    //! @fn PushBack()
    //! @brief Pushes element to the end of stack with enlarging size.
    //! @arg Type element is an element user wants to insert
    //-----------------------------------
    void PushBack(Type element);

    //-----------------------------------
    //! @fn begin()
    //! @brief Returns iterator to first element
    //! @return Array_Iterator<Type> temporary iterator object
    //-----------------------------------
    Array_Iterator<Type> begin();

    //-----------------------------------
    //! @fn begin()
    //! @brief Returns iterator to place after the last element
    //! @return Array_Iterator<Type> temporary iterator object
    //-----------------------------------
    Array_Iterator<Type> end();

    //-----------------------------------
    //! @fn operator=()
    //! @brief moves that to this array
    //-----------------------------------
    Array<Type>& operator=(Array<Type>&& that);

    //-----------------------------------
    //! @fn operator=()
    //! @brief Makes a copy of array "that" by value.
    //! Resizes this if necessary.
    //! @arg Array<Type>& that is a right value of operator
    //! with values user wants to copy from.
    //! @return Array<Type>& link to array with values from "that"
    //-----------------------------------
    Array<Type>& operator=(Array<Type>& that);

    //-----------------------------------
    //! @fn operator[]()
    //! @brief Gives access to an element of array with provided index
    //! @arg int index is an index of demanding element
    //! @return Type&: link to location of demanding element
    //-----------------------------------
    Type& operator[](const int index) const;

    //-----------------------------------
    //! @fn operator+()
    //! @brief Concatenates this array and array from args
    //! @arg Array<Type>& second is an array with future right values
    //! @return Array<Type>& result: result of concatenation
    //-----------------------------------
    Array<Type>& operator+(const Array<Type>& second) const;

    //-----------------------------------
    //! @fn Size()
    //! @brief Returns size (capacity) of array.
    //! @return size_t - how many elements can array store in that time
    //-----------------------------------
    size_t Size() const;

    //-----------------------------------
    //! @fn Dump()
    //! @brief Creates dump of array - size, all elements from,
    //! state and other debug information.
    //-----------------------------------
    void Dump() const;

    //-----------------------------------
    //! @fn Swap()
    //! @brief Swaps fields of this and that Arrays
    //! @arg Array<Type>& that is a reference to Array for swapping
    //-----------------------------------
    void Swap(Array<Type>& that);

    //-----------------------------------
    //! @fn operator+=(Array<Type>& that)
    //! @brief assignment operator implemented with copy&swap algorithm
    //! @arg Array<Type>& that is a reference to source Array
    //-----------------------------------
    Array<Type>& operator+=(Array<Type>& that);

    //-----------------------------------
    //! @fn GetData()
    //! @brief Returns const pointer to the beginning of array
    //! @return pointer
    //-----------------------------------
    const Type* GetData() const
    {
        return(data_);
    }
};

//-----------------------------------
//! @fn operator<<()
//! @brief Dumps array data to output stream
//! @arg std::ostream& ost is a stream user writes to
//! @arg const Array<Type>& that is a array with values to dump
//! @return std::ostream& : reference to output stream user writes to
//-----------------------------------
template <typename Type>
std::ostream& operator<<(std::ostream& ost, const Array<Type>& that);



//===================================

template <typename Type>
Array<Type>::Array()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    size_ = 0;
    data_ = nullptr;
}

template <typename Type>
Array<Type>::Array(const int size)
{
    size_ = size;
    data_ = new Type[size_];
}

template <typename Type>
Array<Type>::Array(Array<Type>&& that):
    size_    (0),
    data_(nullptr)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    Swap(that);
}

template <typename Type>
Array<Type>::Array(Array<Type>& that)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (&that != this)
    {
        size_ = that.Size();
        data_ = new Type[size_];
        std::copy(that.begin(), that.end(), this->begin());
    }
}

template <typename Type>
Array<Type>::Array(const std::initializer_list<Type>& lst)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    size_ = lst.size();
    data_ = new Type[size_];
    std::copy(lst.begin(), lst.end(), this->begin());
}

template <typename Type>
Array<Type>::~Array()
{
    delete[] data_;
    data_ = nullptr;
}

template <typename Type>
Array_Iterator<Type> Array<Type>::begin()
{
    Array_Iterator<Type> it(data_);
    return it;
}

template <typename Type>
Array_Iterator<Type> Array<Type>::end()
{
    Array_Iterator<Type> it(data_+size_);
    return it;
}

template <typename Type>
void Array<Type>::Erase(int index)
{
    if (index < 0 || index >= size_)
        throw Exception::EIndexOutOfRange;
    else
    {
        Type* newData = nullptr;
        if (size_ > 1)
        {
            newData = new Type[size_-1];
            for(int i=0; i<index; ++i)
            {
                newData[i] = data_[i];
            }
            for(int i=index+1; i<size_; ++i)
            {
                newData[i-1] = data_[i];
            }
        }
        delete[] data_;
        data_ = newData;
        size_--;
    }
}

template <typename Type>
void Array<Type>::Insert(int index, Type element)
{
    if (index < 0 || index >= size_)
        throw Exception::EIndexOutOfRange;
    else
    {
        Type* newData = new Type[size_ + 1];
        for( int i = 0; i < index; ++i )
        {
            newData[i] = data_[i];
        }
        newData[index] = element;
        for( int i = index + 1; i < size_ + 1; ++i)
        {
            newData[i] = data_[i-1];
        }
        delete[] data_;
        data_ = newData;
        size_++;
    }

}

template <typename Type>
Type& Array<Type>::operator [](int index) const
{
    if (index < 0 || index >= size_)
    {
        throw Exception::EIndexOutOfRange;
    }
    return data_[index];
}

template <typename Type>
inline void Array<Type>::Swap(Array<Type> &that)
{
    std::swap(this->data_,that.data_);
    std::swap(this->size_,that.size_);
}

template <typename Type>
Array<Type>& Array<Type>::operator+=(Array<Type>& that)
{
    if ( this == &that )
    {
        return *this;
    }
    Array<Type> victim(that);
    Swap(victim);
    return *this;
}

template <typename Type>
Array<Type>& Array<Type>::operator=(Array<Type>& that)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if ( this == &that )
    {
        return *this;
    }
    new (this) Array<Type>(that);
    return *this;
}

template <typename Type>
Array<Type>& Array<Type>::operator=(Array<Type>&& that)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if ( this == &that )
    {
        return *this;
    }
    Swap(that);
    return *this;
}

template <typename Type>
Array<Type>& Array<Type>::operator+(const Array<Type>& second) const
{
    Array<Type>* result = new Array<Type>;

    result->data_ = Concat(data_, second.GetData(), this->size_, second.size_);
    result->size_ = this->size_ + second.size_;
    return *result;
}

template <typename Type>
std::ostream& operator<<(std::ostream& ost, const Array<Type>& that)
{
    size_t size = that.Size();
    ost << "data_[" << size << "]:" << endl;
	for (int i = 0; i < size; ++i)
    {
        ost << "      [" << i << "] = " << (that.GetData())[i] << endl;
    }
    return ost;
}


template <typename Type>
void Array<Type>::Clear()
{
    for (int i=0; i<size_; ++i)
    {
        data_[i] = static_cast<Type>(0);
    }
}

template <typename Type>
void Array<Type>::PushBack(Type element)
{
    Type* newData = Concat(data_, &element, size_);
    delete[] data_;
    data_ = newData;
    size_++;
}

template <typename Type>
size_t Array<Type>::Size() const
{
    return size_;
}

template <typename Type>
void Array<Type>::Dump() const
{
    const char* DUMP_FILENAME = "dumpArray.txt";     //!< name of dump file
    time_t t = time(NULL);                      //!< current system time
    std::ofstream dumpfile(DUMP_FILENAME, std::ofstream::app);
    if (dumpfile.fail())
        throw Exception::EFileCreationError;
    dumpfile << "====== ARRAY DUMP ======" << endl;
    dumpfile << asctime(localtime(&t));
    dumpfile << "ARRAY " << "addr " << data_ << endl;
    dumpfile << *this;
    //-----------------------------------
    //! Show all data in array, even some indexes was never used.
    //-----------------------------------
    dumpfile.close();
}

template <typename Type>
inline Type* Array<Type>::Copy(const Type *that, int first, int last)
{
    int newSize = last-first+1;
    Type* newdata = new Type[newSize];
    for (int i = 0; i < newSize; ++i)
    {
        newdata[i] = that[first+i];
    }
    if (newSize == 0)
    {
        return nullptr;
    }
    return newdata;
}

template <typename Type>
inline Type* Array<Type>::Concat(const Type *left, const Type *right, const size_t leftLen, const size_t rightLen) const
{
    if ( leftLen+rightLen == 0 )
    {
        return nullptr;
    }
    Type* result = new Type[leftLen+rightLen];
    for (int i = 0; i < leftLen; ++i)
        result[i] = left[i];
    for (int i = 0; i < rightLen; ++i)
        result[leftLen+i] = right[i];
    return result;

}

template <typename Type>
inline Type* Array<Type>::Concat(const Type *left, const Type *right, const size_t leftLen) const
{
    Type* result = new Type[leftLen + 1];
    for (int i = 0; i < leftLen; ++i)
        result[i] = left[i];
    result[leftLen] = *right;
    return result;

}


template <typename Type>
void Array<Type>::Resize(int newsize)
{   if( newsize < 0 )
    {
        throw Exception::EBadSize;
    }
    if( newsize == 0 )
    {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
    }
    else
    {
        Type* newdata = new Type[newsize];
        for (int i = 0; i < ((newsize<=size_) ? newsize : size_); ++i)
        {
            newdata[i] = data_[i];
        }
        delete[] data_;
        data_ = newdata;
        size_ = newsize;
    }
}
//
//
//
//



template<>
class Array<bool>
{
public:
    typedef char block_type;
    static const size_t BLOCK_SIZE = sizeof(block_type) * 8;
    class BitReference
    {
    public:
       block_type* ptr_to_block;
       unsigned char number_of_bit;
       BitReference(block_type* ptr, int number);
       operator bool() const
       {
           bool result = ((*ptr_to_block) >> number_of_bit) & 1;
           return result;
       }
       bool operator=(bool right)
       {
           if( right )
           {
               *ptr_to_block = ( ( *ptr_to_block ) | ( 1 << number_of_bit ) );
           }
           else
           {
               *ptr_to_block = ( ( *ptr_to_block ) & ~( 1 << number_of_bit ) );
           }
           return right;
       }
       bool operator=(BitReference right)
       {
           bool result;
           result = *(right.ptr_to_block) & (1 << right.number_of_bit);
           this->operator =(result);
           return result;
       }
    };


    Array();
    Array(size_t size);
    ~Array();
    BitReference& operator[](int index);
    size_t Size();

private:
    size_t size_;
    block_type* data_;
};

Array<bool>::BitReference::BitReference(block_type* ptr, int number)
{
    if( number < 0 || number >= BLOCK_SIZE)
    {
        throw Exception::EIndexOutOfRange;
    }
    ptr_to_block = ptr;
    number_of_bit = number;
}

Array<bool>::Array()
{
    data_ = nullptr;
    size_ = 0;
}

Array<bool>::Array(size_t size)
{
    size_ = size;
    data_ = new block_type[size / BLOCK_SIZE + 1];
    for (int i=0; i<= (size/BLOCK_SIZE); ++i)
    {
        data_[i] = 0;
    }
}

Array<bool>::~Array()
{
    delete[] data_;
}

Array<bool>::BitReference& Array<bool>::operator[](int index)
{
    if( index < 0 || index >= size_ )
    {
        throw Exception::EIndexOutOfRange;
    }
    BitReference* result = new BitReference( data_ + ( index / BLOCK_SIZE ), index % BLOCK_SIZE );
    return *result;

}

size_t Array<bool>::Size()
{
    return size_;
}
#endif // ARRAY_H
