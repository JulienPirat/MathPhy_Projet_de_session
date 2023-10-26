#pragma once
#include <Matrix3.cpp>
#include <Quaternion.h>

/**
* Holds a transform matrix, consisting of a rotation matrix and
* a position. The matrix has 12 elements; it is assumed that the
* remaining four are (0,0,0,1), producing a homogenous matrix.
*/

/**
* Holds an inertia tensor, consisting of a 3x3 row-major matrix.
* * This matrix is not padding to produce an aligned structure, since
* it is most commonly used with a mass (single real) and two
* damping coefficients to make the 12-element characteristics array
* of a rigid body.
*/

class Matrix4
{
public:
	/**
	* Holds the transform matrix data in array form.
	*/
	float data[12];

	/**
* Transform the given vector by this matrix.
*
* @param vector The vector to transform.
*/
	Vector3D operator*(const Vector3D& vector) const
	{
		return Vector3D(
			vector.x * data[0] + vector.y * data[1] +
			vector.z * data[2] + data[3],
			vector.x * data[4] +
			vector.y * data[5] +
			vector.z * data[6] + data[7],
			vector.x * data[8] +
			vector.y * data[9] +
			vector.z * data[10] + data[11]
		);
	}

	/**
* Returns a matrix that is this matrix multiplied by the given
* other matrix.
*/
	Matrix4 operator*(const Matrix4& o) const
	{
		Matrix4 result;
		result.data[0] = (o.data[0] * data[0]) + (o.data[4] * data[1]) +
			(o.data[8] * data[2]);
		result.data[4] = (o.data[0] * data[4]) + (o.data[4] * data[5]) +
			(o.data[8] * data[6]);
		result.data[8] = (o.data[0] * data[8]) + (o.data[4] * data[9]) +
			(o.data[8] * data[10]);
		result.data[1] = (o.data[1] * data[0]) + (o.data[5] * data[1]) +
			(o.data[9] * data[2]);
		result.data[5] = (o.data[1] * data[4]) + (o.data[5] * data[5]) +
			(o.data[9] * data[6]);
		result.data[9] = (o.data[1] * data[8]) + (o.data[5] * data[9]) +
			(o.data[9] * data[10]);
		result.data[2] = (o.data[2] * data[0]) + (o.data[6] * data[1]) +
			(o.data[10] * data[2]);
		result.data[6] = (o.data[2] * data[4]) + (o.data[6] * data[5]) +
			(o.data[10] * data[6]);
		result.data[10] = (o.data[2] * data[8]) + (o.data[6] * data[9]) +
			(o.data[10] * data[10]);
		result.data[3] = (o.data[3] * data[0]) + (o.data[7] * data[1]) +
			(o.data[11] * data[2]) + data[3];
		result.data[7] = (o.data[3] * data[4]) + (o.data[7] * data[5]) +
			(o.data[11] * data[6]) + data[7];
		result.data[11] = (o.data[3] * data[8]) + (o.data[7] * data[9]) +
			(o.data[11] * data[10]) + data[11];
		return result;
	}

	/**
	* Returns the determinant of the matrix.
	*/
	float getDeterminant() const;

	/**
	* Sets the matrix to be the inverse of the given matrix.
	*
	* @param m The matrix to invert and use to set this.
	*/
	void setInverse(const Matrix4& m);

	/** Returns a new matrix containing the inverse of this matrix. */
	Matrix4 inverse() const
	{
		Matrix4 result;
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
* Sets this matrix to be the rotation matrix corresponding to* the given quaternion.
*/
	void setOrientationAndPos(const Quaternion& q, const Vector3D& pos)
	{
		data[0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
		data[1] = 2 * q.i * q.j + 2 * q.k * q.r;
		data[2] = 2 * q.i * q.k - 2 * q.j * q.r;
		data[3] = pos.x;
		data[4] = 2 * q.i * q.j - 2 * q.k * q.r;
		data[5] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
		data[6] = 2 * q.j * q.k + 2 * q.i * q.r;
		data[7] = pos.y;
		data[8] = 2 * q.i * q.k + 2 * q.j * q.r;
		data[9] = 2 * q.j * q.k - 2 * q.i * q.r;
		data[10] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
		data[11] = pos.z;
	}

	/**
* Transform the given vector by the transformational inverse
* of this matrix.
*/
	Vector3D transformInverse(const Vector3D& vector) const
	{
		Vector3D tmp = vector;
		tmp.x -= data[3];
		tmp.y -= data[7];
		tmp.z -= data[11];
		return Vector3D(
			tmp.x * data[0] +
			tmp.y * data[4] +
			tmp.z * data[8],
			tmp.x * data[1] + tmp.y * data[5] + tmp.z * data[9],
			tmp.x * data[2] +
			tmp.y * data[6] +
			tmp.z * data[10]
		);
	}

	/**
* Transform the given direction vector by this matrix.
*/
	Vector3D transformDirection(const Vector3D& vector) const
	{
		return Vector3D(
			vector.x * data[0] +
			vector.y * data[1] +
			vector.z * data[2],
			vector.x * data[4] +
			vector.y * data[5] +
			vector.z * data[6],
			vector.x * data[8] +
			vector.y * data[9] +
			vector.z * data[10]
		);
	}
	/**
* Transform the given direction vector by the
* transformational inverse of this matrix.
*/
	Vector3D transformInverseDirection(const Vector3D& vector) const
	{
		return Vector3D(
			vector.x * data[0] +
			vector.y * data[4] +
			vector.z * data[8],
			vector.x * data[1] +
			vector.y * data[5] +
			vector.z * data[9],
			vector.x * data[2] +
			vector.y * data[6] +
			vector.z * data[10]
		);
	}
};

