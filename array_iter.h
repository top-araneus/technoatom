#ifndef ARRAY_ITER_H
#define ARRAY_ITER_H

template<typename Type>
class Array_Iterator
{
public:

    //!< typedefs for std::copy standarts
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef Type value_type;
    typedef ptrdiff_t difference_type;
    typedef Type* pointer;
    typedef Type& reference;

    //-----------------------------------
    //! @fn Array_Iterator(Type* ptr)
    //! @brief Iterator's constructor
    //! @arg Type* ptr is a pointer to array element
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
    //! @fn bool operator!=()
    //! @brief returns true if two iterators are pointing to different indexes
    //! @arg Array_Iterator& left is a first iterator for comparsion
    //! @arg Array_Iterator& right is a second iterator for comparsion
    //-----------------------------------
    friend bool operator!=(const Array_Iterator<Type>& left, const Array_Iterator<Type>& right)
    {
        return (left.pointer_ != right.pointer_);
    }

    //-----------------------------------
    //! @fn Type& operator*()
    //! @brief returns element iterator is pointing to
    //-----------------------------------
    Type & operator*() const
    {
        if(pointer_ == nullptr)
        {
            throw Exception::EMemAllocError;
        }
        return *pointer_;

    }

private:

    Type *pointer_;
};

#endif // ARRAY_ITER_H
