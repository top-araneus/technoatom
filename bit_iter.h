//-----------------------------------
//! @file bit_iter.h
//! Implements bit reference and bit iterator
//! for operating with Array<bool> elements
//!
//! team araneus, 2017
//-----------------------------------
#ifndef BIT_ITER_H
#define BIT_ITER_H
#include <cstring>

//============================
//! type of data_
//============================
typedef unsigned char block_type; //!< bits are stored in blocks - unsigned char variables
//============================
//! amount of bits in block_type
//============================
const size_t BLOCK_SIZE = sizeof(block_type) * 8;

//-----------------------------------
//! @brief BitReference class
//-----------------------------------
class BitReference
{
protected:
	block_type* ptr_to_block; //!< ptr_to_block is a pointer to block with bit reference is pointing to
	unsigned char number_of_bit; //!< number_of_bit is a number of bit in block
public:

   //-----------------------------------
   //! @fn BitReference(block_type* ptr, size_t number)
   //! @brief Constructor for reference to bit on provided block with number
   //! @arg block_type* ptr is a pointer to block which stores requested bit
   //! @arg size_t number is a number of bit in current block
   //-----------------------------------
   BitReference(block_type* ptr, size_t number)
   {
       if( number >= BLOCK_SIZE)
	   {
		   throw Exception::EIndexOutOfRange;
	   }
	   ptr_to_block = ptr;
	   number_of_bit = number;
   }

   ~BitReference()
   {}

   //-----------------------------------
   //! @fn operator bool() const
   //! @brief Transforming BitReference object to bool value
   //-----------------------------------
   operator bool() const
   {
	   bool result = ((*ptr_to_block) >> number_of_bit) & 1;
	   return result;
   }

   //-----------------------------------
   //! @fn bool operator=(bool right)
   //! @brief assigns bool value to current bit.
   //! Uses logical expressions to change block value:
   //! moves 1 to number of bit and use it as a mask
   //! @arg bool right is a value operator assigns to bit
   //! @return bool: assigned value for complex constructions
   //-----------------------------------
   bool operator=(bool right)
   {
	   if( right )
	   {
           *ptr_to_block = ( ( *ptr_to_block ) | ( 1 << number_of_bit ) );
	   }
	   else
	   {
		   *ptr_to_block = ( ( *ptr_to_block ) & ~( 1 << number_of_bit ) );
	   }
	   return right;
   }

   //-----------------------------------
   //! @fn bool operator=(bool right)
   //! @brief assigns value got from BitReference to current bit
   //! @arg BitReference right is a right value of operator refers to demanded bit
   //! @return bool: assigned value for complex constructions
   //-----------------------------------
   bool operator=(BitReference right)
   {
	   bool result;
	   result = *(right.ptr_to_block) & (1 << right.number_of_bit);
	   this->operator =(result);
	   return result;
   }

   //-----------------------------------
   //! @fn BitReference& operator++()
   //! @brief Iterator feature. Gets next bit in block array
   //! @return BitReference&: link to changed reference
   //-----------------------------------
   BitReference& operator++()
   {
	   if (number_of_bit == BLOCK_SIZE-1)
	   {
		   ptr_to_block++;
		   number_of_bit = 0;
	   }
	   else
	   {
		   number_of_bit++;
	   }
	   return *this;
   }

   //-----------------------------------
   //! @fn virtual bool operator!=(const BitReference& right)
   //! @brief Compares references by value.
   //! @arg BitReference right is a right value for comparing
   //! @return true if bits are unequal
   //-----------------------------------
   friend bool operator!=(const BitReference& left, const BitReference& right)
   {
	   return ((bool)left != (bool)right);
   }

   //-----------------------------------
   //! @fn BitReference& operator*()
   //! @brief Operating with BitReference as a pointer
   //! is unuseful due to type transforming feature
   //! @return link to this object
   //-----------------------------------
   BitReference& operator*()
   {
	   return *this;
   }
};

//===================================

//-----------------------------------
//! @brief BitIterator class is a BitReference hair with changed != operator.
//! When BitReference compares objects by values, BitIterator compares it by references.
//-----------------------------------
class BitIterator : public BitReference
{
   public:
   BitIterator(block_type* ptr, int number) : //!< Constructor is same with BitReference
       BitReference(ptr, number)
   {}

   ~BitIterator()
   {}

   //!< typedefs for std::copy
   typedef std::output_iterator_tag iterator_category;
   typedef bool value_type;
   typedef ptrdiff_t difference_type;
   typedef bool* pointer;
   typedef bool& reference;

   //-----------------------------------
   //! @fn virtual bool operator!=(const BitReference& right)
   //! @brief Compares references
   //! @arg BitReference right is a right BitReference for comparing
   //! @return true if pointers to blocks or numbers of bit are unequal
   //-----------------------------------
   friend bool operator!=(const BitIterator& left, const BitIterator& right)
    {
	    return ((left.ptr_to_block != right.ptr_to_block) || (left.number_of_bit != right.number_of_bit));
    }
};

#endif // BIT_ITER_H
