#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "Vector3D.h"

namespace Math
{
	/**
	 * @brief The Matrix3D class
	 *
	 * Computation for Matrices on Processor-side with float precision (Opengl uses float)
	 *
	 * Row and Column count starts at 0!!!, like in Computer Science, not like Match
	 *
	 * matrix[row][col] is the interpretation of the data!
	 */
	class Matrix3D
	{
	public:
		/**
		 * @brief Matrix3D initializes the matrix to all zero
		 */
		Matrix3D();

		/**
		 * @brief loadIdendity sets the matrix to the idendity matrix
		 *
		 * \sa idendity
		 */
		void loadIdendity();

		/**
		 * @brief setRow
		 * @param nbr defines which row should be set (0-2)
		 * @param row defines the values for the row
		 *
		 * matrix[row][col] is the interpretation of the data!
		 *
		 * \sa Vector3D
		 */
		void setRow(int nbr, Vector3D& row);

		/**
		 * @brief setColumn
		 * @param nbr defines which column should be set (0-2)
		 * @param col defines the values for the column
		 *
		 * matrix[row][col] is the interpretation of the data!
		 *
		 * \sa Vector3D
		 */
		void setColumn(int nbr, Vector3D& col);

		/**
		 * @brief getRow
		 * @param nbr which row is used. (0-2)
		 * @return the wanted row
		 *
		 * matrix[row][col] is the interpretation of the data!
		 *
		 * \sa Vector3D
		 */
		Vector3D getRow(int nbr);


		/**
		 * @brief getColumn
		 * @param nbr which col is used (0-2)
		 * @return the wanted column
		 *
		 * matrix[row][col] is the interpretation of the data!
		 *
		 * \sa Vector3D
		 */
		Vector3D getColumn(int nbr);

		/**
		 * @brief at gives acces to the value at the position [row][col]
		 * @param row
		 * @param col
		 * @return value at [row][col]
		 */
		float at(int row, int col) const;

		/**
		 * @brief at_ref gives access and the possibility to change the matrix at [row][col]
		 * @param row
		 * @param col
		 * @return reference to [row][col]
		 */
		float& at_ref(int row, int col);

		/**
		 * @brief operator + addition of 2 matrices
		 * @param m
		 * @return
		 */
		Matrix3D& operator+(const Matrix3D& m);

		/**
		 * @brief operator - subtraction of 2 matrices
		 * @param m
		 * @return
		 */
		Matrix3D& operator-(const Matrix3D& m);

		/**
		 * @brief operator [] access the matrix in row i
		 * @param i which row of matrix, 0 based
		 * @return reference to the row
		 */
		Vector3D& operator[](int i);

		/**
		 * @brief operator [] const version of access operator
		 * @param i
		 * @return
		 *
		 * \sa operator[]
		 */
		const Vector3D& operator[](int i) const;

		/**
		 * @brief print just for debugging purposes
		 */
		void print() const;

	private:
		Vector3D data[3];
	};


//	/**
//	 * @brief idendity
//	 * @return idendity matrix for dimensional
//	 */
//	Matrix3D idendity();

//	/**
//	 * @brief translate returns a translation matrix for given translationvector
//	 * @param v where w != 0, otherwise translation has no effect
//	 * @return
//	 */
//	Matrix3D translate(Vector3D& v);
//	Matrix3D translate(float x, float y, float z);

//	/**
//	 * @brief scale returns a scaling matrix for given scalevector
//	 * @param v
//	 * @return
//	 */
//	Matrix3D scale(Vector3D& v);
//	Matrix3D scale(float x, float y, float z);

//	/**
//	 * @brief rotate returns a rotationmatrix for a given rotationaxis and an angle in degree
//	 * @param v
//	 * @return
//	 */
//	Matrix3D rotate(Vector3D& v,float angle);
//	Matrix3D rotate(float x, float y, float z, float angle);
}



#endif // Matrix3D_H
