///-----------------------------------
//! @file print.h
//! Custom print function.
//!
//! author SultanovAR, 2017
//-----------------------------------
#ifndef PRINT_H
#define PRINT_H

#include "iostream"

//====================================
//! @brief writes argument to console.
//! @arg const char*
//! @return void
//====================================
void print (const char* str)
{
	while (*str)
	{
		std::cout << *str++;
	}
}

//=====================================
//! @brief Auxiliary function for detecting a special symbol
//! special symbol is '/#'
//! @arg const char*
//! @return bool
//====================================
bool CheckSpecialSymbol(const char* str)
{
	return (*str == '/' && *(str+1) == '#');
}

//=====================================================================================
//! @brief this function works like a classic printf,
//! but without type specificators (%d) instead of '%' need to write '/#'
//! @arg const char* - What will be output and in what will be replaced spec. symbols
//! @arg Type - variable that will be placed instead of spec. symbol
//! @arg Args... - other variables which will be placed instead of spec. symbols
//=====================================================================================
template <typename Type, typename... Args>
void print(const char* str, Type value, Args... args)
{
	while (*str)
	{
		if (!CheckSpecialSymbol(str))
		{
			std::cout << *str++;
		}
		else
		{

			std::cout << value;
			print(str+2,args...);
			break;
		}
	}
}

//====================================
//! @brief writes argument to output stream.
//! @arg std::ostream& ost is a output stream to write
//! @arg const char*
//! @return void
//====================================
void print (std::ostream& ost, const char* str)
{
    while (*str)
    {
        ost << *str++;
    }
}

//=====================================================================================
//! @brief this function works like a fprintf,
//! but without type specificators (%d) instead of '%' need to write '/#'
//! and can write to any ostream user provides
//! @arg std::ostream& ost is a output stream to write
//! @arg const char* - What will be output and in what will be replaced spec. symbols
//! @arg Type - variable that will be placed instead of spec. symbol
//! @arg Args... - other variables which will be placed instead of spec. symbols
//=====================================================================================
template <typename Type, typename... Args>
void print(std::ostream& ost, const char* str, Type value, Args... args)
{
    while (*str)
    {
        if (!CheckSpecialSymbol(str))
        {
            ost << *str++;
        }
        else
        {

            ost << value;
            print(ost,str+2,args...);
            break;
        }
    }
}

#endif // PRINT_H
