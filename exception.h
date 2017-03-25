//-----------------------------------
//! @file exception.h
//! Exception codes for catching inside program
//!
//! author faradaym, 2017
//-----------------------------------
#ifndef EXCEPTION_H
#define EXCEPTION_H

#define EXCEPT(ERRCODE,DESC,PARENT) \
Exception(ERRCODE, DESC, __FILE__, __LINE__, PARENT) \

#include <exception>
class Exception : public std::exception
{
public:
    static const int EStackIsEmpty = 0x5E;    //!< Exception index when stack is empty
    static const int EMemAllocError = 0xAE;   //!< Exception index when memory wasn't allocated in heap
    static const int EDataCorrupted = 0xDC;   //!< Exception index when data aren't ok
    static const int EFileCreationError = 0xFC;   //!< Exception index when file wasn't created
    static const int EBadSize = 0xB5;   //!< Exception when new size of array is less than zero
    static const int EIndexOutOfRange = 0x10;   //!< Exception when index is out of range
    static const int ETestFailed = 0x7F;
    static const int EIterHasNoArray = 0x1A;
    static const int EDullException = 0xDE;
    int errcode_;
    char* description_;
    char* file_;
    int line_;
    Exception* parent_;

    Exception()
    {
        errcode_ = EDullException;
        description_ = const_cast<char*>("Dull user-generated exception");
        file_ = const_cast<char*>("");
        line_ = 0xBADA55;
        parent_ = nullptr;
    }

    Exception(int errcode, char* description, char* file, int line, Exception* parent)
    {
        errcode_ = errcode;
        description_ = description;
        file_ = file;
        line_ = line;
        parent_ = parent;
    }

};

std::ostream& operator<<(std::ostream& ost, Exception& exc)
{
    print(ost, "Exception: code /#, reason: /# \n file: /#, line /# \n", exc.errcode_, exc.description_, exc.file_, exc.line_);
    if (exc.parent_ != nullptr)
    {
        ost << "|Parent: " << *(exc.parent_);
    }
    return ost;
}

#endif // EXCEPTION_H
