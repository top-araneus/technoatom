#ifndef ARRAY_ITER_H
#define ARRAY_ITER_H

template<typename Type>
class Array_Iterator
{
public:

    //!< typedefs for std::copy standarts
    typedef bidirectional_iterator_tag iterator_category;
    typedef Type value_type;
    typedef ptrdiff_t difference_type;
    typedef Type* pointer;
    typedef Type& reference;

    //-----------------------------------
    //! @fn Array_Iterator(Array<Type> *parent)
    //! @brief Iterator's constructor
    //! @arg Array<Type> *parent is an array iterator is used for
    //-----------------------------------
    Array_Iterator(Array<Type> *parent)
    {
        parent_ = parent;
        index_ = 0;
    }

    //-----------------------------------
    //! @fn Array_Iterator& operator++()
    //! @brief Increments size of operator
    //-----------------------------------
    Array_Iterator & operator++()
    {
        OK()
        index_++;
        return *this;
    }

    //-----------------------------------
    //! @fn Array_Iterator& begin()
    //! @brief returns iterator pointing to begin of array
    //-----------------------------------
    Array_Iterator & begin()
    {
        OK()
        Array_Iterator* It = new Array_Iterator(parent_);
        return *It;
    }

    //-----------------------------------
    //! @fn Array_Iterator& end()
    //! @brief returns iterator pointing to end of array
    //-----------------------------------
    Array_Iterator & end()
    {
        OK()
        Array_Iterator* It = new Array_Iterator(parent_);
        It->index_ = parent_->Size();
        return *It;
    }

    //-----------------------------------
    //! @fn bool operator!=()
    //! @brief returns true if two iterators are pointing to different indexes
    //! @arg Array_Iterator& that is a second iterator for comparsion
    //-----------------------------------
    bool operator!=(const Array_Iterator & that) const
    {
        return that.isUnEqual(index_);
    }

    //-----------------------------------
    //! @fn Type& operator*()
    //! @brief returns element iterator is pointing to
    //-----------------------------------
    Type & operator*() const
    {
        OK()
        if(parent_->GetData() == nullptr)
        {
            throw Exception::EMemAllocError;
        }
        if(index_ >= parent_->Size())
        {
            throw Exception::EIndexOutOfRange;
        }
        return (*(parent_))[index_];

    }

    //-----------------------------------
    //! @fn bool isUnEqual(const size_t that_index)
    //! @brief compares indexes
    //! @arg size_t that_index is a second index to compare
    //-----------------------------------
    bool isUnEqual(const size_t that_index) const
    {
        OK()
        return index_ != that_index;
    }

    size_t index_;
private:

    Array<Type> *parent_;
};

#endif // ARRAY_ITER_H
