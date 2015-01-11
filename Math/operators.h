#ifndef OPERATORS_H
#define OPERATORS_H

/**
 * @file Here are the Declaration of all Algebraic Operations between vectors and matrices
 */
namespace Math
{
#include "Vector4D.h"
#include "Matrix4D.h"

	//----------------------------------------------------------------------------------------------
	// VECTORS ONLY
	//----------------------------------------------------------------------------------------------
	Math::Vector4D scalarProduct(Math::Vector4D v1, Math::Vector4D v2);


	//----------------------------------------------------------------------------------------------
	// VECTORS AND MATRICES
	//----------------------------------------------------------------------------------------------
	/**
	 * @brief operator * usual matrix times vector multiplication
	 * @param m
	 * @param v
	 * @return transformed vector
	 */
	Math::Vector4D operator*(Math::Matrix4D& m, Math::Vector4D& v);

	//----------------------------------------------------------------------------------------------
	// MATRICES ONLY
	//----------------------------------------------------------------------------------------------
	/**
	 * @brief operator * usual matrix multiplication with 2 matrices
	 * @param m1
	 * @param m2
	 * @return new matrix
	 */
	Math::Matrix4D operator*(Math::Matrix4D& m1, Math::Matrix4D& m2);
}


#endif // OPERATORS_H
