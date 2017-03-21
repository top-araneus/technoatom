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
#include "array_iter.h"
#include "bit_iter.h"
using namespace std;

//-----------------------------------
//! @brief Array class. Type is a type of elements array stores.
//-----------------------------------

template <typename Type>
class Array
{
private:
    //-----------------------------------
    //! @var int size is a capacity of array
    //-----------------------------------
    int size_;

    //-----------------------------------
    //! @var Type * data is a container with elements
    //-----------------------------------

    Type* data_;

public:

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

    Array();
    //-----------------------------------
    //! @fn Array(int size)
    //! @brief Constructs array with defined size
    //! @arg int size is a number of elements array can store
    //-----------------------------------
    Array(const int size);

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
	//! @arg int index is a future index of element in array . diaposone = [0...size_].
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
	Array<Type>& operator+(const Array<Type>& that) const;

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
	void Dump();

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
    const Type* GetData() const;
};

//-----------------------------------
//! @fn operator<<()
//! @brief Dumps array data to output stream
//! @arg std::ostream& ost is a stream user writes to
//! @arg const Array<Type>& that is a array with values to dump
//! @return std::ostream& : reference to output stream user writes to
//-----------------------------------
template <typename Type>
std::ostream& operator<<(std::ostream& ost, Array<Type>& that);



//-----------------------------------------------------------------=

template <typename Type>
Array<Type>::Array()
{
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
Array<Type>::Array(Array<Type>&& that)
{
	size_ = 0;
	data_ = nullptr;
    Swap(that);
}

template <typename Type>
Array<Type>::Array(Array<Type>& that)
{
    if (&that != this)
    {
		data_ = new Type[that.Size()];
		size_ = that.Size();
        std::copy(that.begin(), that.end(), this->begin());
    }
}

template <typename Type>
Array<Type>::Array(const std::initializer_list<Type>& lst)
{
    data_ = new Type[size_];
	size_ = lst.size();
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
	Array_Iterator<Type> it(data_ + size_);
    return it;
}

template <typename Type>
const Type* Array<Type>::GetData() const
{
    return(data_);
}

template <typename Type>
void Array<Type>::Erase(int index)
{
	if ( size_ == 0)
		return;
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
	if (index < 0 || index > size_)
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
Array<Type>& Array<Type>::operator=(Array<Type>& that)
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
Array<Type>& Array<Type>::operator+=(Array<Type>& that)
{
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
    if ( this == &that )
    {
        return *this;
    }
    Swap(that);
    return *this;
}

template <typename Type>
Array<Type>& Array<Type>::operator+(const Array<Type>& that) const
{
	if (size_ + that.Size() == 0)
	{
		Array<Type>* result = new Array<Type>;
		return *result;
	}
	Array<Type>* result = new Array<Type>(size_ + that.Size());
	for (int i = 0; i < size_; ++i)
		(*result)[i] = (*this)[i];
	for (int i = 0; i < that.Size(); ++i)
		(*result)[size_ + i] = that[i];
    return *result;
}

template <typename Type>
std::ostream& operator<<(std::ostream& ost, Array<Type>& that)
{
    size_t size = that.Size();
    ost << "data_[" << size << "]:" << endl;
	for (int i = 0; i < size; ++i)
    {
        ost << "      [" << i << "] = " << that[i] << endl;
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
	Insert(size_, element);
}

template <typename Type>
size_t Array<Type>::Size() const
{
    return size_;
}

template <typename Type>
void Array<Type>::Dump()
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
inline void Array<Type>::Resize(int newsize)
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
	//-----------------------------------------------------------------
	//! block_type and BLOCK_SIZE described in file "bit_iter.h"
	//-----------------------------------------------------------------

	Array();
	//-----------------------------------
	//! @fn Array(int size)
	//! @brief Constructs array with defined size
	//! @arg int size is a number of elements array can store
	//-----------------------------------
    Array(size_t size);
    ~Array();
	//----------------------------------
	//! @brief copy constructor that uses std::copy
	//----------------------------------
    Array(Array<bool>& that);

	//----------------------------------
	//! @brief move constructor that uses copy and swap semantic
	//----------------------------------
    Array(Array<bool>&& that);

	//-----------------------------------------------------------------
	//! @brief copy assignment
	//-----------------------------------------------------------------
    Array<bool>& operator=(Array<bool>& that);

	//-----------------------------------------------------------------
	//! @brief move assignment
	//-----------------------------------------------------------------
    Array<bool>& operator=(Array<bool>&& that);

	//-----------------------------------------------------------------
	//! @brief writes to file "dump.txt" all information about Array
	//-----------------------------------------------------------------
    void Dump();

	//-----------------------------------------------------------------
	//! @brief shell of std::swap,interchanging fields of objects
	//-----------------------------------------------------------------
    inline void Swap(Array<bool>& that);

	//-----------------------------------------------------------------
	//! @brief concatenation of two Arrays in one and returns new Array
	//! @arg Array<bool>& - second part of result Array
	//! @return Array<bool>& - new Array that is result of concatenation
	//-----------------------------------------------------------------
    Array<bool>& operator+(Array<bool>& that);

	//-----------------------------------
	//! @fn Array(std::initializer_list lst)
	//! @brief initialization constructor
	//-----------------------------------
    Array(const std::initializer_list<bool>& lst);

	//-----------------------------------------------------------------
	//! returns element with needed index
	//! @arg int - index of element in Array
	//! @return BitReference& - pointer to bit
	//-----------------------------------------------------------------
    BitReference& operator[](int index);

	//-----------------------------------------------------------------
	//! @brief size_ getter
	//-----------------------------------------------------------------
    size_t Size() const;

	//-----------------------------------
	//! @fn Resize()
	//! @brief Changes capacity of array (how many elements can it store).
	//! Deletes last elements if new size is less than old size.
	//! @arg int newsize is new capacity of array
	//-----------------------------------
    void Resize(size_t size);

	//-----------------------------------
	//! @fn Clear()
	//! @brief Removes all elements from array with saving size.
	//-----------------------------------
    void Clear();

	//-----------------------------------
	//! @fn Erase()
	//! @brief Removes element from array, translocating right elements
	//! @arg int index is index of the element that will be deleted
	//-----------------------------------
    void Erase(int index);

	//-----------------------------------
	//! @fn Insert()
	//! @brief Inserts element to the array, translocating right elements
	//! @arg int index is a future index of element in array . diaposone = [0...size_].
	//! @arg bool element is an element user wants to insert
	//-----------------------------------
    void Insert(int index, bool element);

	//-----------------------------------
	//! @fn PushBack()
	//! @brief Pushes element to the end of stack with enlarging size.
	//! @arg Type element is an element user wants to insert
	//-----------------------------------
    void PushBack(bool element);

	//-----------------------------------
	//! @fn begin()
	//! @brief Returns iterator to begin of Array
	//! @return BitIterator temporary iterator object
	//-----------------------------------
    BitIterator begin();

	//-----------------------------------
	//! @fn begin()
	//! @brief Returns iterator to place after the last element
	//! @return BitIterator temporary iterator object
	//-----------------------------------
    BitIterator end();


    const block_type* GetData() const;
private:
    size_t size_;
    block_type* data_;

};

std::ostream& operator<<(std::ostream& ost, Array<bool>& that)
{
    size_t size = that.Size();
    ost << "data_[" << size << "]:" << endl;
    for (int i = 0; i < size; ++i)
    {
        ost << "      [" << i << "] = " << that[i] << endl;
    }
    return ost;
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

Array<bool>::Array(Array<bool>&& that)
{
	size_ = 0;
	data_ = nullptr;
    Swap(that);
}

Array<bool>::Array(Array<bool>& that)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (&that != this)
    {
        size_ = that.Size();
        data_ = new block_type[size_ / BLOCK_SIZE + 1];
        std::copy(that.begin(), that.end(), this->begin());
    }
}

Array<bool>& Array<bool>::operator=(Array<bool>&& that)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if ( this == &that )
    {
        return *this;
    }
    Swap(that);
    return *this;
}

Array<bool>& Array<bool>::operator=(Array<bool>& that)
{
    if ( this == &that )
    {
        return *this;
    }
    Array<bool> victim(that);
    Swap(victim);
    return *this;
}

void Array<bool>::Dump()
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

Array<bool>::~Array()
{
    delete[] data_;
}

Array<bool>::Array(const std::initializer_list<bool>& lst)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    size_ = lst.size();
    data_ = new block_type[size_ / BLOCK_SIZE + 1];
    std::copy(lst.begin(), lst.end(), this->begin());
}

BitReference& Array<bool>::operator[](int index)
{
    if( index < 0 || index >= size_ )
    {
        throw Exception::EIndexOutOfRange;
    }
    BitReference* result = new BitReference( data_ + ( index / BLOCK_SIZE ), index % BLOCK_SIZE );
    return *result;

}

Array<bool>& Array<bool>::operator+(Array<bool>& second)
{
    if ((Size() + second.Size()) == 0)
    {
        Array<bool>* result = new Array<bool>;
        return *result;
    }

    Array<bool>* result = new Array<bool>(Size() + second.Size());
    for (int i=0; i<Size(); ++i)
    {
        (*result)[i] = (*this)[i];
    }
    for (int i=Size(); i<(Size()+second.Size()); ++i)
    {
        (*result)[i] = second[i-Size()];
    }
    result->size_ = this->size_ + second.size_;
    return *result;
}

size_t Array<bool>::Size() const
{
    return size_;
}

void Array<bool>::Resize(size_t size)
{
	if (size == 0)
	{
		delete[] data_;
		data_ = nullptr;
		size_ = 0;
	}
    if (( size < ((size_ / BLOCK_SIZE) + 1) * BLOCK_SIZE) && (size >= size_ - (size_ % BLOCK_SIZE)))
    {
        size_ = size;
        return;
    }
    else
    {
        block_type* newdata = new block_type[size / BLOCK_SIZE + 1];
        if (data_ != nullptr)
        {
            for (int i = 0; i <= (size > size_ ? size_/BLOCK_SIZE : size/BLOCK_SIZE); ++i)
            {
                newdata[i] = data_[i];
            }
            delete[] data_;
        }
        data_ = newdata;
        size_ = size;
    }
}

void Array<bool>::Clear()
{
    for (int i = 0; i <= size_/BLOCK_SIZE; ++i)
        {
            data_[i] = 0;
        }
}

inline void Array<bool>::Swap(Array<bool> &that)
{
    std::swap(this->data_,that.data_);
    std::swap(this->size_,that.size_);
}

void Array<bool>::Erase(int index)
{
    for (int i = index; i < size_-1; ++i)
    {
        (*this)[i] = (*this)[i+1];
    }
    Resize(size_ - 1);
    if (size_ == 0)
    {
        delete[] data_;
        data_ = nullptr;
    }
}

void Array<bool>::Insert(int index, bool element)
{
	if (index < 0 || index > size_)
		throw Exception::EIndexOutOfRange;
    Resize(size_ + 1);
    for (int i = index+1; i < size_; i++)
    {
        (*this)[i] = (*this)[i-1];
    }
    (*this)[index] = element;
}

void Array<bool>::PushBack(bool element)
{
    Insert(size_, element);
}

BitIterator Array<bool>::begin()
{
    BitIterator bit(data_, 0);
    return bit;
}

BitIterator Array<bool>::end()
{
    if (size_ % BLOCK_SIZE == BLOCK_SIZE-1)
    {
        BitIterator bit(data_ + (size_/BLOCK_SIZE + 1) , 0);
        return bit;
    }
    BitIterator bit(data_ + (size_/BLOCK_SIZE) , size_ % BLOCK_SIZE + 1);
    return bit;
}

const block_type* Array<bool>::GetData() const
{
    return(data_);
}

#endif // ARRAY_H
