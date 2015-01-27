#include "Math/Vector4D.h"
#include "Math/Vector3D.h"
#include "Math/Matrix4D.h"
#include "System\Log.h"
#include <iostream>



int main()
{
	Math::Vector4D v, n(1, 2, 3, 1);
	Math::Vector3D z(5, 2, 3);
	Math::Matrix4D m = Math::translate(3, 0, 0);
	m.print();

	//std::cout << v.x() << std::endl;

	//std::cout << (v + n).z() << std::endl;

	v = m * n;

	Log() << "Hallo Welt, ich bin ein Logger";

	//v = z + n;
	//for(auto i = 0; i < 4; i++)
	//	std::cout << i << " = " << z[i] << std::endl;

	int i;
	std::cin >> i;

	return 0;
}
