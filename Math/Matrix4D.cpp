// has to be filled

namespace Math
{

	Math::Matrix4D::Matrix4D()
	{
		for(auto i = 0; i < 4; i++)
			for(auto j = 0; j < 4; j++)
				data[i][j] = 0;
	}

	void Math::Matrix4D::setRow(int nbr, Math::Vector4D& row)
	{

	}

	void Math::Matrix4D::setColumn(int nbr, Math::Vector4D& col)
	{

	}

	void Math::Matrix4D::loadIdendity()
	{
		for(auto i = 0; i < 4; i++)
			data[i][i] = 1;
	}

	Math::Vector4D Math::Matrix4D::getRow(int nbr)
	{

	}

	Math::Vector4D Math::Matrix4D::getColumn(int nbr)
	{

	}

	Math::Matrix4D Math::idendity()
	{
		Matrix4D m;
		m.loadIdendity();
		return m;
	}

}
