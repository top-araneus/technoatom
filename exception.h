//-----------------------------------
//! @file exception.h
//! Exception codes for catching inside program
//!
//! author faradaym, 2017
//-----------------------------------
#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception
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
        Exception();
};

#endif // EXCEPTION_H
