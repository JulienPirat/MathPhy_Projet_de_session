#pragma once
#include <Vector3D.h>
#include <Quaternion.h>

/**
* Holds an inertia tensor, consisting of a 3x3 row-major matrix.
* This matrix is not padding to produce an aligned structure, since
* it is most commonly used with a mass (single real) and two
* damping coefficients to make the 12-element characteristics array
* of a rigid body.
*/

class Matrix3
{
public:
	/**
	* Holds the tensor matrix data in array form.
	*/
	float data[9];

	///Constructeur

	Matrix3() {
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;
		data[4] = 0;
		data[5] = 0;
		data[6] = 0;
		data[7] = 0;
		data[8] = 0;
	}

	Matrix3(float d1, float d2, float d3, float d4, float d5, float d6, float d7, float d8, float d9) {
		data[0] = d1;
		data[1] = d2;
		data[2] = d3;
		data[3] = d4;
		data[4] = d5;
		data[5] = d6;
		data[6] = d7;
		data[7] = d8;
		data[8] = d9;
	}

	/**
	* Returns a matrix that is this matrix multiplied by the given
	* other matrix.
	*/
	Matrix3 operator*(const Matrix3& o) const
	{
		return Matrix3(
			data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6],
			data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7],
			data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8],
			data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6],
			data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7],
			data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8],
			data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6],
			data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7],
			data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8]
		);
	}

	/**
* Sets the matrix to be the inverse of the given matrix.
*
* @param m The matrix to invert and use to set this.
*/
	void setInverse(const Matrix3& m)
	{
		float t4 = m.data[0] * m.data[4];
		float t6 = m.data[0] * m.data[5];
		float t8 = m.data[1] * m.data[3];
		float t10 = m.data[2] * m.data[3];
		float t12 = m.data[1] * m.data[6];
		float t14 = m.data[2] * m.data[6];
		// Calculate the determinant.
		float t16 = (t4 * m.data[8] - t6 * m.data[7] - t8 * m.data[8] +
			t10 * m.data[7] + t12 * m.data[5] - t14 * m.data[4]);
		// Make sure the determinant is non-zero.
		if (t16 == (float)0.0f) return;
		float t17 = 1 / t16;
		data[0] = (m.data[4] * m.data[8] - m.data[5] * m.data[7]) * t17;
		data[1] = -(m.data[1] * m.data[8] - m.data[2] * m.data[7]) * t17;
		data[2] = (m.data[1] * m.data[5] - m.data[2] * m.data[4]) * t17;
		data[3] = -(m.data[3] * m.data[8] - m.data[5] * m.data[6]) * t17;
		data[4] = (m.data[0] * m.data[8] - t14) * t17;
		data[5] = -(t6 - t10) * t17;
		data[6] = (m.data[3] * m.data[7] - m.data[4] * m.data[6]) * t17;
		data[7] = -(m.data[0] * m.data[7] - t12) * t17;
		data[8] = (t4 - t8) * t17;
	}
	/** Returns a new matrix containing the inverse of this matrix. */
	Matrix3 inverse() const
	{
		Matrix3 result;
		result.setInverse(*this);
		return result;
	}
	/**
	* Inverts the matrix.
	*/
	void invert()
	{
		setInverse(*this);
	}

	/**
* Sets the matrix to be the transpose of the given matrix.
*
* @param m The matrix to transpose and use to set this.
*/
	void setTranspose(const Matrix3& m)
	{
		data[0] = m.data[0];
		data[1] = m.data[3];
		data[2] = m.data[6];
		data[3] = m.data[1];
		data[4] = m.data[4];
		data[5] = m.data[7];
		data[6] = m.data[2];
		data[7] = m.data[5];
		data[8] = m.data[8];
	}
	/** Returns a new matrix containing the transpose of this matrix. */
	Matrix3 transpose() const
	{
		Matrix3 result;
		result.setTranspose(*this);
		return result;
	}

	/**
* Sets this matrix to be the rotation matrix corresponding to
* the given quaternion.
*/
	void setOrientation(const Quaternion& q)
	{
		data[0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
		data[1] = 2 * q.i * q.j + 2 * q.k * q.r;
		data[2] = 2 * q.i * q.k - 2 * q.j * q.r;
		data[3] = 2 * q.i * q.j - 2 * q.k * q.r;
		data[4] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
		data[5] = 2 * q.j * q.k + 2 * q.i * q.r;
		data[6] = 2 * q.i * q.k + 2 * q.j * q.r;
		data[7] = 2 * q.j * q.k - 2 * q.i * q.r;
		data[8] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
	}

	/**
* Sets the matrix values from the given three vector components.
* These are arranged as the three columns of the vector.
*/
	void setComponents(const Vector3D& compOne, const Vector3D& compTwo,
		const Vector3D& compThree)
	{
		data[0] = compOne.x;
		data[1] = compTwo.x;
		data[2] = compThree.x;
		data[3] = compOne.y;
		data[4] = compTwo.y;
		data[5] = compThree.y;
		data[6] = compOne.z;
		data[7] = compTwo.z;
		data[8] = compThree.z;
	}

	/**
* Sets the matrix to be a skew-symmetric matrix based on
* the given vector. The skew-symmetric matrix is the equivalent
* of the vector product. So if a,b are vectors, a x b = A_s b
* where A_s is the skew-symmetric form of a.
*/
	void setSkewSymmetric(const Vector3D vector)
	{
		data[0] = data[4] = data[8] = 0;
		data[1] = -vector.z;
		data[2] = vector.y;
		data[3] = vector.z;
		data[5] = -vector.x;
		data[6] = -vector.y;
		data[7] = vector.x;
	}
};

