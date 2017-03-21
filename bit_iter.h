#ifndef BIT_ITER_H
#define BIT_ITER_H
#include <cstring>

//============================
//! type of data_
//============================
typedef unsigned char block_type;
//============================
//! amount of bits in block_type
//============================
const size_t BLOCK_SIZE = sizeof(block_type) * 8;

class BitReference
{
public:
   block_type* ptr_to_block;
   unsigned char number_of_bit;

   BitReference(block_type* ptr, int number)
   {
	   if( number < 0 || number >= BLOCK_SIZE)
	   {
		   throw Exception::EIndexOutOfRange;
	   }
	   ptr_to_block = ptr;
	   number_of_bit = number;
   }

   operator bool() const
   {
	   bool result = ((*ptr_to_block) >> number_of_bit) & 1;
	   return result;
   }

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

   bool operator=(BitReference right)
   {
	   bool result;
	   result = *(right.ptr_to_block) & (1 << right.number_of_bit);
	   this->operator =(result);
	   return result;
   }

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

   virtual bool operator!=(const BitReference& right)
   {
	   return ((bool)(*this) != (bool)right);
   }

   BitReference& operator*()
   {
	   return *this;
   }
};

class BitIterator : public BitReference
{
   public:
   BitIterator(block_type* ptr, int number) :
       BitReference(ptr, number)
    {}

   typedef std::bidirectional_iterator_tag iterator_category;
   typedef bool value_type;
   typedef ptrdiff_t difference_type;
   typedef bool* pointer;
   typedef bool& reference;
    virtual bool operator!=(const BitReference& right)
    {
	    return (((*this).ptr_to_block != right.ptr_to_block) || ((*this).number_of_bit != right.number_of_bit));
    }
};


#endif // BIT_ITER_H
