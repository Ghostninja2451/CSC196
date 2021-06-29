#include "Helper.h"
#include "dynamic.h"
#include <iostream>

int main()
{
	std::cout << henry::sqr(5) << std::endl;

	henry::point p1{ 10, 10 };
	henry::point p2{ 10, 10 };
	henry::point p3 = p1 + p2;

	std::cout << p3.x << " " << p3.y << std::endl;

	system("pause");
}
