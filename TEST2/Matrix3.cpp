#include "Matrix3.h"

Matrix3 Matrix3::operator*(const Matrix3& matrix) const
{
	return Matrix3(
		data[0] * matrix.data[0] + data[1] * matrix.data[3] + data[2] * matrix.data[6],
		data[0] * matrix.data[1] + data[1] * matrix.data[4] + data[2] * matrix.data[7],
		data[0] * matrix.data[2] + data[1] * matrix.data[5] + data[2] * matrix.data[8],
		data[3] * matrix.data[0] + data[4] * matrix.data[3] + data[5] * matrix.data[6],
		data[3] * matrix.data[1] + data[4] * matrix.data[4] + data[5] * matrix.data[7],
		data[3] * matrix.data[2] + data[4] * matrix.data[5] + data[5] * matrix.data[8],
		data[6] * matrix.data[0] + data[7] * matrix.data[3] + data[8] * matrix.data[6],
		data[6] * matrix.data[1] + data[7] * matrix.data[4] + data[8] * matrix.data[7],
		data[6] * matrix.data[2] + data[7] * matrix.data[5] + data[8] * matrix.data[8]
	);
}

Vector3D Matrix3::operator*(const Vector3D& vector) const
{
	return Vector3D(
		vector.x * data[0] + vector.y * data[3] + vector.z * data[6],
		vector.x * data[1] + vector.y * data[4] + vector.z * data[7],
		vector.x * data[2] + vector.y * data[5] + vector.z * data[8]
	);
}

Matrix3 Matrix3::operator*(const double scalaire) const
{
	return Matrix3(
		scalaire * data[0], scalaire * data[3], scalaire * data[6],
		scalaire * data[1], scalaire * data[4], scalaire * data[7],
		scalaire * data[2], scalaire * data[5], scalaire * data[8]
	);
}

Matrix3 Matrix3::operator+(const Matrix3& matrix) const
{
	return Matrix3(
		data[0] + matrix.data[0], data[1] + matrix.data[1], data[2] + matrix.data[2],
		data[3] + matrix.data[3], data[4] + matrix.data[4], data[5] + matrix.data[5],
		data[6] + matrix.data[6], data[7] + matrix.data[7], data[8] + matrix.data[8]
	);
}

Matrix3 Matrix3::Inverse()
{
	Matrix3 inverseMatrix;
	inverseMatrix.MakeInverse(*this);
	return inverseMatrix;
}

Matrix3 Matrix3::Transpose()
{
	Matrix3 transposeMatrix;
	transposeMatrix.MakeTranspose(*this);
	return transposeMatrix;
}

void Matrix3::setOrientation(const Quaternion& q)
{
	//BENJ NTK
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

void Matrix3::MakeInverse(const Matrix3& m)
{
	//BENJ NTK
	double t4 = m.data[0] * m.data[4];
	double t6 = m.data[0] * m.data[5];
	double t8 = m.data[1] * m.data[3];
	double t10 = m.data[2] * m.data[3];
	double t12 = m.data[1] * m.data[6];
	double t14 = m.data[2] * m.data[6];
	// Calculate the determinant.
	double t16 = (t4 * m.data[8] - t6 * m.data[7] - t8 * m.data[8] +
		t10 * m.data[7] + t12 * m.data[5] - t14 * m.data[4]);
	// Make sure the determinant is non-zero.
	if (t16 == (float)0.0f) return;
	double t17 = 1 / t16;
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

void Matrix3::MakeTranspose(const Matrix3& m)
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

Matrix3 operator*(const double& a, const Matrix3& m)
{
	return Matrix3(
		a * m.data[0], a * m.data[1], a * m.data[2],
		a * m.data[3], a * m.data[4], a * m.data[5],
		a * m.data[6], a * m.data[7], a * m.data[8]
	);
}

Vector3D operator*(const Vector3D& v, const Matrix3& m)
{
	return Vector3D(
		v.x * m.data[0] + v.y * m.data[1] + v.z * m.data[2],
		v.x * m.data[3] + v.y * m.data[4] + v.z * m.data[5],
		v.x * m.data[6] + v.y * m.data[7] + v.z * m.data[8]
	);
}
