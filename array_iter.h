#ifndef ARRAY_ITER_H
#define ARRAY_ITER_H

template<typename Type>
class Array_Iterator
{
public:

    //!< typedefs for std::copy standarts
    typedef Type value_type;
    typedef ptrdiff_t difference_type;
    typedef Type* pointer;
    typedef Type& reference;

    //-----------------------------------
    //! @fn Array_Iterator(Array<Type> *parent)
    //! @brief Iterator's constructor
    //! @arg Array<Type> *parent is an array iterator is used for
    //-----------------------------------
    Array_Iterator(Type* ptr)
    {
        pointer_ = ptr;
    }

    //-----------------------------------
    //! @fn Array_Iterator& operator++()
    //! @brief Increments size of operator
    //-----------------------------------
    Array_Iterator & operator++()
    {
        pointer_++;
        return *this;
    }

    //-----------------------------------

    //-----------------------------------
    //! @fn bool operator!=()
    //! @brief returns true if two iterators are pointing to different indexes
    //! @arg Array_Iterator& that is a second iterator for comparsion
    //-----------------------------------
    {
    }

    //-----------------------------------
    //! @fn Type& operator*()
    //! @brief returns element iterator is pointing to
    //-----------------------------------
    Type & operator*() const
    {
        {
            throw Exception::EMemAllocError;
        }

    }

private:

};

#endif // ARRAY_ITER_H
