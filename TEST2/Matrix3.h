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

	///Attributes

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

	///Operators 

	//Combination of linear transformation
	Matrix3 operator*(const Matrix3& matrix) const;

	//Transform of a Vector 
	Vector3D operator*(const Vector3D& vector) const;

	///Methodes

	//Get the Inverse Matrix
	Matrix3 Inverse();

	//Get the transpose matrix
	Matrix3 Transpose();

	//Set the matrix base on a quaternion
	void setOrientation(const Quaternion& q);

	//Overload the operator * between double and Matrix3
	friend Matrix3 operator*(const double& a, const Matrix3& m);

private :

	void MakeInverse(const Matrix3& m);
	void MakeTranspose(const Matrix3& m);
};

