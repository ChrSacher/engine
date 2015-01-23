#include "Vector2D.h"


namespace Math
{
	float scalarProduct(const Math::Vector2D& v1, const Math::Vector2D& v2)
	{
		return v1.x() * v2.x() + v1.y() * v2.y();
	}

}
