#ifndef OPERATORS_H
#define OPERATORS_H

/**
 * @file Here are the Declaration of all Algebraic Operations between vectors and matrices
 */

#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"


namespace Math
{
	//----------------------------------------------------------------------------------------------
	// VECTORS ONLY
	//----------------------------------------------------------------------------------------------
	float scalarProduct(Vector4D v1, Vector4D v2);


	//----------------------------------------------------------------------------------------------
	// VECTORS AND MATRICES
	//----------------------------------------------------------------------------------------------
	/**
	 * @brief operator * usual matrix times vector multiplication
	 * @param m
	 * @param v
	 * @return transformed vector = m * v
	 */
	Vector4D operator*(Matrix4D& m, Vector4D& v);

	//----------------------------------------------------------------------------------------------
	// MATRICES ONLY
	//----------------------------------------------------------------------------------------------
	/**
	 * @brief operator * usual matrix multiplication with 2 matrices
	 * @param m1
	 * @param m2
	 * @return new matrix = m1 * m2
	 */
	Matrix4D operator*(Matrix4D& m1, Matrix4D& m2);
}


#endif // OPERATORS_H
