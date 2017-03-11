#ifndef ARRAY_ITER_H
#define ARRAY_ITER_H

template<typename Type>
class Array_Iterator
{
public:
    typedef output_iterator_tag iterator_category;
    typedef Type value_type;
    typedef ptrdiff_t difference_type;
    typedef Type* pointer;
    typedef Type& reference;
    Array_Iterator(Array<Type> *parent)
    {
        parent_ = parent;
        index_ = 0;
    }

    Array_Iterator & operator++()
    {
        OK()
        index_++;
        return *this;
    }

    Array_Iterator & begin()
    {
        OK()
        Array_Iterator* It = new Array_Iterator(parent_);
        return *It;
    }

    Array_Iterator & end()
    {
        OK()
        Array_Iterator* It = new Array_Iterator(parent_);
        It->index_ = parent_->Size();
        return *It;
    }

    bool operator!=(const Array_Iterator & that) const
    {
        OK()
        return that.isUnEqual(index_);

    }

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
