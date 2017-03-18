#ifndef PRINT_H
#define PRINT_H

void print (const char* str)
{
	while (*str) std::cout << *str++;
}

template <typename Type, typename... Args>
void print(const char* str, Type value, Args... args)
{
	while (*str)
	{
		if (*str != '#') std::cout << *str++;
		else
		{
			std::cout << value;
			print(str+1,args...);
			break;
		}
	}
}

#endif // PRINT_H
