//-----------------------------------
//! @file array.h
//! Implements array class
//!
//! team araneus, 2017
//-----------------------------------
#ifndef ARRAY_H
#define ARRAY_H
#define OK() \
    if(parent_ == nullptr) throw Exception::EIterHasNoArray;
#include "exception.h"
#include <ctime>
#include <typeinfo>
#include <cstdlib>
#include <fstream>
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

        //-----------------------------------
        //! @fn Array(const Array& that)
        //! @brief Copy constructor
        //! @arg Array& that is a link to array user wants to copy from
        //-----------------------------------
        Array(Array& that);

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

        void Swap(Array<Type>& that);//documentary


		//-----------------------------------
		//! @fn GetData()
		//! @brief Returns const pointer to the beginig of array
		//! @return pointer
		//-----------------------------------
		const Type* GetData() const
		{
			return(data_);
		}

        //-----------------------------------
        //! @var iter
        //! @brief Iterator for this array
        //-----------------------------------
     };

    #include "array_iter.h"

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
        size_ = 0;
        data_ = new Type[size_];
    }

    template <typename Type>
    Array<Type>::Array(const int size)
    {
        size_ = size;
        data_ = new Type[size_];
    }

    template <typename Type>
    Array<Type>::Array(Array<Type>& that)
    {
        size_ = that.Size();
        data_ = new Type[size_];
        Array_Iterator<Type>* i_in = new Array_Iterator<Type>(&that);
        Array_Iterator<Type>* i_out = new Array_Iterator<Type>(this);
        std::copy(i_in->begin(), i_in->end(), i_out->begin());
        delete i_in;
        delete i_out;
        /* data_ = Copy(that.GetData(), 0, size_-1);*/
    }

    template <typename Type>
    Array<Type>::~Array()
    {
        delete[] data_;
        data_ = nullptr;
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
    void Array<Type>::Swap(Array<Type> &that)
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
        for (int i=0; i<size; ++i)
        {
            ost << "      [" << i << "] = " << (that.GetData())[i] << endl;
        }
        return ost;
    }

    template <typename Type>
    void Array<Type>::Clear()
    {
        //TODO: NULLING NEW

        /*delete[] data_;
        data_ = new Type[size_]; */

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


#endif // ARRAY_H
