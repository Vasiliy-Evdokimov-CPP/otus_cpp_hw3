#include <iostream>
#include <map>
#include "my_allocator.hpp"
#include "my_container.hpp"

const int ITEMS_AMOUNT = 10;

int factorial(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++)
        result *= i;
    return result;
}

int main()
{
    std::cout << "default allocated map:" << std::endl;
    std::map<int, int> map_default;
	for (int i = 0; i < ITEMS_AMOUNT; ++i) 
    {
		map_default[i] = factorial(i);
        std::cout << i << " " << map_default[i] << std::endl;
    }
    //
    std::cout << "custom allocated map:" << std::endl;
    std::map<int, int, std::less<>, my_allocator<std::pair<const int, int>, ITEMS_AMOUNT>> map_custom;
	for (int i = 0; i < ITEMS_AMOUNT; ++i)
    {
		map_custom[i] = factorial(i);
        std::cout << i << " " << map_custom[i] << std::endl;
    }
    //
	my_container<int> container_default;
	for (int i = 0; i < ITEMS_AMOUNT; ++i)
		container_default.add(i);
    std::cout << "default allocated container:" << std::endl;
    container_default.iterate();
    //
    my_container<int, my_allocator<int, ITEMS_AMOUNT>> container_custom;
	for (int i = 0; i < ITEMS_AMOUNT; ++i)
	    container_custom.add(i);
    std::cout << "custom allocated container:" << std::endl;
    container_custom.iterate();
}