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

#define  __FL__ \
    __FILE__, __LINE__ \

#include <exception>
#include <iomanip>

class Exception : public std::exception
{
public:
   /* static const int _StackIsEmpty = 0x5E;    //!< Exception index when stack is empty
    static const int _MemAllocError = 0xAE;   //!< Exception index when memory wasn't allocated in heap
    static const int _DataCorrupted = 0xDC;   //!< Exception index when data aren't ok
    static const int _FileCreationError = 0xFC;   //!< Exception index when file wasn't created
    static const int _BadSize = 0xB5;   //!< Exception when new size of array is less than zero
    static const int _IndexOutOfRange = 0x10;   //!< Exception when index is out of range
    static const int _TestFailed = 0x7F;
    static const int _IterHasNoArray = 0x1A;
    static const int _DullException = 0xDE;
    static const int _NullDereference = 0x0D;*/
    Exception()
    {
        errcode_ = 0xDE;
        description_ = const_cast<char*>("Dull user-generated exception");
        file_ = const_cast<char*>("");
        line_ = -1;
        parent_ = nullptr;
    }

    Exception(int errcode, char* description, char* file, int line, Exception* parent = nullptr)
    {
        errcode_ = errcode;
        description_ = description;
        file_ = file;
        line_ = line;
        parent_ = parent;
    }


    const char* what() const throw()
    {
        return description_;
    }

    int GetErrorCode() const throw()
    {
        return errcode_;
    }

    const char* GetDescription() const throw()
    {
        return const_cast<char*>(description_);
    }

    const char* GetFileFrom() const throw()
    {
        return const_cast<char*>(file_);
    }

    int GetLineFrom() const throw()
    {
        return line_;
    }

    Exception* GetParent() const throw()
    {
        return parent_;
    }

    bool operator==(Exception that)
    {
        return (GetErrorCode() == that.GetErrorCode());
    }

    bool operator!=(Exception that)
    {
        return !(*this == that);
    }

protected:
    int errcode_;
    const char* description_;
    char* file_;
    int line_;
    Exception* parent_;

};


std::ostream& operator<<(std::ostream& ost, Exception& exc)
{
    print(ost, "Exception: code /#, reason: /# \n file: /#, line /# \n", exc.GetErrorCode(), exc.GetDescription(), exc.GetFileFrom(), exc.GetLineFrom());
    if (exc.GetParent() != nullptr)
    {
        ost << "|Parent: " << *(exc.GetParent());
    }
    return ost;
}


class EStackIsEmpty : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    EStackIsEmpty() throw() :
        Exception(0x5E, "Stack is empty", "", -1, nullptr)    {    }

    EStackIsEmpty(char* file, int line, Exception* parent = nullptr) throw() :
        Exception(0x5E, "Stack is empty", file, line, parent)    {    }
};

class EMemAllocError : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    EMemAllocError() throw() :
        Exception(0xAE, "Memory allocation error", "", -1, nullptr)    {    }

    EMemAllocError(char* file, int line, Exception* parent = nullptr) throw() :
        Exception(0xAE, "Memory allocation error", file, line, parent)    {    }
};

class EDataCorrupted : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    EDataCorrupted() throw():
        Exception(0xDC, "Data is corrupted", "", -1, nullptr)    {    }

    EDataCorrupted(char* file, int line, Exception* parent = nullptr) throw():
        Exception(0xDC, "Data is corrupted", file, line, parent)    {    }
};

class EFileCreationError : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    EFileCreationError() throw():
        Exception(0xFC, "File creation error", "", -1, nullptr)    {    }

    EFileCreationError(char* file, int line, Exception* parent = nullptr) throw():
        Exception(0xFC, "File creation error", file, line, parent)    {    }
};

class EBadSize : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    EBadSize() throw():
        Exception(0xB5, "Bad size. Check index", "", -1, nullptr)    {    }

    EBadSize(char* file, int line, Exception* parent = nullptr) throw():
        Exception(0xB5, "Bad size. Check index", file, line, parent)    {    }
};

class EIndexOutOfRange : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    EIndexOutOfRange() throw():
        Exception(0x10, "Index is out of range", "", -1, nullptr)    {    }

    EIndexOutOfRange(char* file, int line, Exception* parent = nullptr) throw():
        Exception(0x10, "Index is out of range", file, line, parent)    {    }
};

class ETestFailed : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    ETestFailed() throw():
        Exception(0x7F, "Unit test failed", "", -1, nullptr)    {    }

    ETestFailed(char* file, int line, Exception* parent = nullptr) throw():
        Exception(0x7F, "Unit test failed", file, line, parent)    {    }
};

class EIterHasNoArray : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    EIterHasNoArray() throw():
        Exception(0x1A, "Tried to initialize iterator without array", "", -1, nullptr)    {    }

    EIterHasNoArray(char* file, int line, Exception* parent = nullptr) throw():
        Exception(0x1A, "Tried to initialize iterator without array", file, line, parent)    {    }
};

class EDullException : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    EDullException() throw():
        Exception(0xDE, "Dull user-generated exception", "", -1, nullptr)    {    }

    EDullException(char* file, int line, Exception* parent = nullptr) throw():
        Exception(0xDE, "Dull user-generated exception", file, line, parent)    {    }
};

class ENullDereference : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    ENullDereference() throw():
        Exception(0x0D, "Tried to dereference null pointer", "", -1, nullptr)    {    }

    ENullDereference(char* file, int line, Exception* parent = nullptr) throw():
        Exception(0x0D, "Tried to dereference null pointer", file, line, parent)    {    }
};

class EALUBadInstruction : public Exception
{
public:
    using Exception::operator ==;
    using Exception::operator !=;
    EALUBadInstruction() throw():
        Exception(0xAB, "Bad instruction in ALU code", "", -1, nullptr)    {    }

    EALUBadInstruction(char* file, int line, Exception* parent = nullptr) throw():
        Exception(0xAB, "Bad instruction in ALU code", file, line, parent)    {    }
};

#endif // EXCEPTION_H
