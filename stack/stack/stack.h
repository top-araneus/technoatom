#ifndef STACK_H
#define STACK_H
#include "array.h"
//-----------------------------------
//! @file stack.h
//! Implements a stack class
//!
//! author faradaym, 2017
//-----------------------------------

using namespace std;
//-----------------------------------
//! Stack class
//-----------------------------------
template<typename value_type>
class Stack
{
public:
   static const size_t POISON_INT = 0xBADA558D;        //!< Number for detecting zombie objects after destruction

    Stack();
    //----------------------------------
    //! @brief Copy constructor that creates true copy of object
    //! @arg Stack& that is a stack to be copied
    //----------------------------------
    Stack(const Stack& that);
    //------------------------------------
    //! Destructor
    //! @brief Removes container and free ynamic memory
    //------------------------------------
    ~Stack();
    //-----------------------------------
    //! Gets a value of top element in a stack
    //! @return value of top element
    //-----------------------------------
    value_type top();

    //-----------------------------------
    //! Checks if stack is empty
    //! @return true if stack is empty, false if not
    //-----------------------------------
    bool empty();

    //-----------------------------------
    //! Getting size of stack
    //! @return size of stack
    //-----------------------------------
    size_t size() const;

    //-----------------------------------
    //! Getting current capacity of stack
    //! @return capacity of stack
    //-----------------------------------
    size_t capacity() const;

    //-----------------------------------
    //! Pushes a value in the stack
    //! @param value is an element to be pushed
    //-----------------------------------
    void push(value_type value);

    //-----------------------------------
    //! Gets top element from the stack and remove it
    //! @return value of top element
    //-----------------------------------
    value_type pop();

    //-----------------------------------
    //! Verifies size and capacity relation
    //! Capacity changes due to pushing and popping data,
    //! and divides to SIZE_STEP every time.
    //! @return true if 0 <= capacity-size <= SIZE_STEP, and capacity % SIZE_STEP == 0.
    //-----------------------------------
    bool ok();

    //-----------------------------------
    //! Creates dump of stack state.
    //! DUMP_FILENAME constant inside function is a name of dump file.
    //! Dump contains size and capacity of stack in the moment,
    //! checks data integrity and show all elements from area in heap.
    //! Elements that are used by stack are marked by *.
    //! Last indexes may contain garbage, because dynamic memory area is raw.
    //! New dumps will be written to the end of file with a timestamp.
    //-----------------------------------
    void dump();

    //-----------------------------------
    //! Copying operator.
    //! Use as: *s1 = *s2 where s1, s2 are pointers to stack objects.
    //! @arg Stack& rArg is a stack to be copied
    //! @return link to left value
    //-----------------------------------
    Stack& operator=(Stack& rArg);


private:
    static const size_t SIZE_STEP = 42;   //!< When stack is full, its capacity will be increased to this value
    size_t capacity_;                     //!< Max number of elements stack can contain without enlarging
    size_t size_;                   //!< Number of elements in a stack now
    Array<value_type>* data_;
};
//-----------------------------------
template<typename value_type>
Stack<value_type>::Stack()
{
    capacity_ = SIZE_STEP;
    data_ = new Array<value_type>(capacity_);
 /*   if (data_->GetData() == nullptr)
        throw EMemAllocError(__FL__);*/
    size_ = 0;
}
//-----------------------------------
template<typename value_type>
Stack<value_type>::Stack(const Stack<value_type>& that)
{
    if (&that != this)
    {
        this->data_ = new Array<value_type>(that.capacity());
        this->size_ = that.size();
        this->capacity_ = that.capacity();
        for (size_t i = 0; i<size_; ++i)
            (*data_)[i] = (*(that.data_))[i];
    }
}
//-----------------------------------
template<typename value_type>
Stack<value_type>::~Stack()
{
    delete data_;
}
//-----------------------------------
template<typename value_type>
Stack<value_type>& Stack<value_type>::operator=(Stack<value_type>& rArg)
{
    if (&rArg != this)
    {
        data_->Resize(0);
        data_->Resize(rArg.capacity());
        this->size_ = rArg.size();
        this->capacity_ = rArg.capacity();
        for (size_t i = 0; i<size_; ++i)
            (*data_)[i] = (*(rArg.data_))[i];
    }
    return *this;
}
//-----------------------------------
template<typename value_type>
value_type Stack<value_type>::top()
{
    if (size_ != 0)
    {
        return (*data_)[ size_-1 ];
    }
    else
    {
        throw EStackIsEmpty(__FL__);
    }
}
//-----------------------------------
template<typename value_type>
bool Stack<value_type>::empty()
{
    return !( (bool)size_ );   //!< true if stack_size == 0
}
//-----------------------------------
template<typename value_type>
size_t Stack<value_type>::size() const
{
    return size_;
}
//-----------------------------------
template<typename value_type>
size_t Stack<value_type>::capacity() const
{
    return capacity_;
}
//-----------------------------------
template<typename value_type>
void Stack<value_type>::push(value_type value)
{
    if (size_ == capacity_-1)                                       //!< stack is full
    {
        capacity_ += SIZE_STEP;
        data_->Resize(capacity_);
    }
    (*data_)[size_++] = value;
}
//-----------------------------------
template<typename value_type>
value_type Stack<value_type>::pop()
{
    if (size_ != 0)
    {
        if (capacity_-size_ > SIZE_STEP)
        {
            capacity_ -= SIZE_STEP;
            data_->Resize(capacity_);
        }
        return (*data_)[--size_];   //!< dont forget to decrease stack size
    }
    else
        throw EStackIsEmpty(__FL__);
}
//-----------------------------------
template<typename value_type>
bool Stack<value_type>::ok()
{
    //!< smth strange if returns false - memory is corrupted
    return ( capacity_-size_ <= SIZE_STEP )&&( capacity_-size_ >= 0 )&&(capacity_ % SIZE_STEP == 0);
}
//-----------------------------------
template<typename value_type>
void Stack<value_type>::dump()
{
    const char* DUMP_FILENAME = "dump.txt";     //!< name of dump file
    time_t t = time(NULL);                      //!< current system time
    std::ofstream dumpfile(DUMP_FILENAME, std::ofstream::app);
    if (dumpfile.fail())
        throw EFileCreationError(__FL__);
    dumpfile << "====== STACK DUMP ======" << endl;
    dumpfile << asctime(localtime(&t));
    dumpfile << "STACK " << (ok() ? "(OK)" : "(ERROR)") << endl;
    dumpfile << "size:     = " << size_ << (size_ == POISON_INT ? " (POISON_INT)" : "") << endl;
    dumpfile << "capacity: = " << capacity_ << (capacity_ == POISON_INT ? " (POISON_INT)" : "") << endl;
    dumpfile << "data[" << capacity_ << "]:" << endl << "   {" << endl;
    //-----------------------------------
    //! Show all data in stack, even some indexes was never used.
    //-----------------------------------
    for (size_t cnt = 0; cnt < capacity_; ++cnt)
    {
        dumpfile << ( cnt < size_ ? " * [" : "   [" ) << cnt << "] = " << (*data_)[cnt] << endl;
    }
    dumpfile.close();
}
#endif
