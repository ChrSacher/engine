/**
 *
 */

namespace Math
{
	class Vector4D;

	/**
	 * @brief The Matrix4D class
	 *
	 * Computation for Matrices on Processor-side with a numerical type Scalar
	 * Use it best with float!
	 */
	template<typename Scalar>
	class Matrix4D
	{
	public:
		Matrix4D();

	private:
		Scalar data[4][4];
	};
}
