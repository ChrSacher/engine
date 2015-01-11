#include "operators.h"


namespace Math
{

	float scalarProduct(Vector4D v1, Vector4D v2)
	{
		return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() + v1.w() * v2.w();
	}

	Vector4D operator*(Matrix4D& m, Vector4D& v)
	{
		Vector4D res;

		for(auto i = 0; i < 4; i++)
			for(auto j = 0; j < 4; j++)
				res[i]+= m.at(i, j) * v[j];

		return res;
	}

}
