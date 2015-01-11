#include "Math/Vector4D.h"
#include <iostream>



int main()
{
	Math::Vector4D v, n(1, 2, 3);

	std::cout << v.x() << std::endl;

	std::cout << (v + n).z() << std::endl;

	return 0;
}
