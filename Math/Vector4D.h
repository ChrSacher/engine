#ifndef VECTOR4D
#define VECTOR4D


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
		Vector4D(float x, float y, float z, float w = 0)
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

		/**
		 * @brief add addtion of vectors, chances this vector!!
		 * @param v
		 * @return
		 */
		Vector4D& add(const Vector4D& v);

		/**
		 * @brief subtract subtraction of vectors, chances this vector!!
		 * @param v
		 * @return
		 */
		Vector4D& subtract(const Vector4D& v);

		/**
		 * @brief scalarProduct calculates the scalar product of the 2 vectors
		 * @param v
		 * @return
		 *
		 * \sa
		 */
		float scalarProduct(const Vector4D& v);

		/**
		 * @brief print for debugging purposes
		 */
		void print() const;

		float operator[](int index) const;
		float& operator[](int index);


	private:
		float data[4];
	};


	/**
	 * @brief operator + addition of vectors, won't change any vector
	 * @param v
	 * @param w
	 * @return new result-vector
	 *
	 * e.g. z = x + y;
	 */
	Vector4D operator+(const Vector4D& v, const Vector4D& w);

	/**
	 * @brief operator - subtraction of vectors, won't change any vector
	 * @param v
	 * @param w
	 * @return new result-vector
	 *
	 * e.g. z = x - y;
	 */
	Vector4D operator-(const Vector4D& v, const Vector4D& w);
}

#endif
