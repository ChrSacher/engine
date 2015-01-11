// has to be filled

namespace Math
{

	/**
	 * @brief __epsilon is for checking on zero
	 * This variable is needed, because floatingpoint operation are not superaccurate,
	 * so you should rather check on epsilon then on equality.
	 */
	const float __epsilon = 0.001;
	/**
	 * @brief The Vector4D class implements a 4d vector with precision float
	 *
	 * The 4th coordinate has a special meaning. It is for easing mathematics in computergfx.
	 *
	 * w == 0 --> vector is a direction/Vector
	 * w == 1 --> vector is a point in space
	 */
	class Vector4D
	{
	public:
		/**
		 * @brief Vector4D initialize to zero
		 */
		Vector4D() :
			Vector4D(0.f, 0.f, 0.f, 0.f)
		{

		}

		/**
		 * @brief Vector4D initalize by value
		 * @param x
		 * @param y
		 * @param z
		 * @param w
		 */
		Vector4D(float x, float y, float z, float w)
		{
			data[0] = x;
			data[1] = y;
			data[2] = z;
			data[3] = w;
		}

		float x() const { return data[0]; }
		void x(float x) { data[0] = x; }
		float y() const { return data[1]; }
		void y(float y) { data[1] = y; }
		float z() const { return data[2]; }
		void z(float z) { data[2] = z; }
		float w() const { return data[3]; }
		void w(float w) { data[3] = w; }

		/**
		 * @brief isDirection gives information about the kind of vector this object represents
		 * @return true, when w is zero
		 *
		 * \sa Vector4D
		 */
		bool isDirection() const { return data[3] <= __epsilon; }

		/**
		 * @brief isPoint gives information about the kind of vector this object represents
		 * @return true, when w is not zero
		 *
		 * \sa Vector4D
		 */
		bool isPoint() const { return !isDirection(); }

	private:
		float data[4];
	};
}
