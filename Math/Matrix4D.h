#ifndef MATRIX4D
#define MATRIX4D

/**
 * @file This file declares Matrices
 */


#include "Vector4D.h"

namespace Math
{
	/**
	 * @brief The Matrix4D class
	 *
	 * Computation for Matrices on Processor-side with float precision (Opengl uses float)
	 *
	 * Row and Column count starts at 0!!!, like in Computer Science, not like Match
	 *
	 * matrix[row][col] is the interpretation of the data!
	 */
	class Matrix4D
	{
	public:
		/**
		 * @brief Matrix4D initializes the matrix to all zero
		 */
		Matrix4D();

		/**
		 * @brief loadIdendity sets the matrix to the idendity matrix
		 *
		 * \sa idendity
		 */
		void loadIdendity();

		/**
		 * @brief setRow
		 * @param nbr defines which row should be set (0-3)
		 * @param row defines the values for the row
		 *
		 * matrix[row][col] is the interpretation of the data!
		 *
		 * \sa Vector4D
		 */
		void setRow(int nbr, Vector4D& row);

		/**
		 * @brief setColumn
		 * @param nbr defines which column should be set (0-3)
		 * @param col defines the values for the column
		 *
		 * matrix[row][col] is the interpretation of the data!
		 *
		 * \sa Vector4D
		 */
		void setColumn(int nbr, Vector4D& col);

		/**
		 * @brief getRow
		 * @param nbr which row is used. (0-3)
		 * @return the wanted row
		 *
		 * matrix[row][col] is the interpretation of the data!
		 *
		 * \sa Vector4D
		 */
		Vector4D getRow(int nbr);

		/**
		 * @brief getColumn
		 * @param nbr which col is used (0-3)
		 * @return the wanted column
		 *
		 * matrix[row][col] is the interpretation of the data!
		 *
		 * \sa Vector4D
		 */
		Vector4D getColumn(int nbr);

		/**
		 * @brief operator + addition of 2 matrices
		 * @param m
		 * @return
		 */
		Matrix4D& operator+(const Matrix4D& m);

		/**
		 * @brief operator - subtraction of 2 matrices
		 * @param m
		 * @return
		 */
		Matrix4D& operator-(const Matrix4D& m);

	private:
		float data[4][4];
	};


	Matrix4D idendity();
}

#endif
