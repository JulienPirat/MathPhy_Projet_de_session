#pragma once
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

	///Attributes

	float data[12];

	///Operators

	//Combinaison of affine transformation
	Matrix4 operator*(const Matrix4& matrix) const;

	//Transform of a vector
	Vector3D operator*(const Vector3D& vector) const;

	///Methodes

	//Get the Inverse matrix
	Matrix4 Inverse();

	//Set the matrix base on a quaternion and a position
	void SetOrientationAndPosition(const Quaternion& q, const Vector3D& p);

	//Transform a position
	Vector3D TransformPosition(const Vector3D& vector);

	//Transform a direction by ignoring the translation
	Vector3D TransformDirection(const Vector3D& vector);

private: 

	float getDeterminant() const;
	void MakeInverse(const Matrix4& m);
};

