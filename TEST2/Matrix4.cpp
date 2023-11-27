#include "Matrix4.h"

Vector3D Matrix4::operator*(const Vector3D& vector) const
{
	return Vector3D(
		vector.x * data[0] + vector.y * data[1] + vector.z * data[2] + data[3],
		vector.x * data[4] + vector.y * data[5] + vector.z * data[6] + data[7],
		vector.x * data[8] + vector.y * data[9] + vector.z * data[10] + data[11]
	);
}

Matrix4 Matrix4::operator*(const Matrix4& matrix) const
{
	Matrix4 result;
	result.data[0] = (matrix.data[0] * data[0]) + (matrix.data[4] * data[1]) + (matrix.data[8] * data[2]);
	result.data[4] = (matrix.data[0] * data[4]) + (matrix.data[4] * data[5]) + (matrix.data[8] * data[6]);
	result.data[8] = (matrix.data[0] * data[8]) + (matrix.data[4] * data[9]) + (matrix.data[8] * data[10]);
	result.data[1] = (matrix.data[1] * data[0]) + (matrix.data[5] * data[1]) + (matrix.data[9] * data[2]);
	result.data[5] = (matrix.data[1] * data[4]) + (matrix.data[5] * data[5]) + (matrix.data[9] * data[6]);
	result.data[9] = (matrix.data[1] * data[8]) + (matrix.data[5] * data[9]) + (matrix.data[9] * data[10]);
	result.data[2] = (matrix.data[2] * data[0]) + (matrix.data[6] * data[1]) + (matrix.data[10] * data[2]);
	result.data[6] = (matrix.data[2] * data[4]) + (matrix.data[6] * data[5]) + (matrix.data[10] * data[6]);
	result.data[10] = (matrix.data[2] * data[8]) + (matrix.data[6] * data[9]) + (matrix.data[10] * data[10]);
	result.data[3] = (matrix.data[3] * data[0]) + (matrix.data[7] * data[1]) + (matrix.data[11] * data[2]) + data[3];
	result.data[7] = (matrix.data[3] * data[4]) + (matrix.data[7] * data[5]) + (matrix.data[11] * data[6]) + data[7];
	result.data[11] = (matrix.data[3] * data[8]) + (matrix.data[7] * data[9]) + (matrix.data[11] * data[10]) + data[11];
	return result;
}

Matrix4 Matrix4::Inverse()
{
	Matrix4 inverseMatrix;
	inverseMatrix.MakeInverse(*this);
	return inverseMatrix;
}

void Matrix4::SetOrientationAndPosition(const Quaternion& q, const Vector3D& p)
{
	data[0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
	data[1] = 2 * q.i * q.j + 2 * q.k * q.r;
	data[2] = 2 * q.i * q.k - 2 * q.j * q.r;
	data[3] = p.x;
	data[4] = 2 * q.i * q.j - 2 * q.k * q.r;
	data[5] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
	data[6] = 2 * q.j * q.k + 2 * q.i * q.r;
	data[7] = p.y;
	data[8] = 2 * q.i * q.k + 2 * q.j * q.r;
	data[9] = 2 * q.j * q.k - 2 * q.i * q.r;
	data[10] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
	data[11] = p.z;
}

Vector3D Matrix4::TransformPosition(const Vector3D& vector)
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

Vector3D Matrix4::TransformDirection(const Vector3D& vector)
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

Matrix3 Matrix4::ToMatrix3()
{
	return Matrix3(
		data[0], data[1], data[2], 
		data[3], data[4], data[5],
		data[6], data[7], data[8]
	);
}

float Matrix4::getDeterminant() const
{
	//BENJ NTK
	return data[8] * data[5] * data[2] +
		data[4] * data[9] * data[2] +
		data[8] * data[1] * data[6] -
		data[0] * data[9] * data[6] -
		data[4] * data[1] * data[10] +
		data[0] * data[5] * data[10];
}

void Matrix4::MakeInverse(const Matrix4& m)
{
	//BENJ NTK
	// Make sure the determinant is non-zero.
	float det = getDeterminant();
	if (det == 0) return;
	det = ((float)1.0) / det;
	data[0] = (-m.data[9] * m.data[6] + m.data[5] * m.data[10]) * det;
	data[4] = (m.data[8] * m.data[6] - m.data[4] * m.data[10]) * det;
	data[8] = (-m.data[8] * m.data[5] + m.data[4] * m.data[9] * m.data[15]) * det;
	data[1] = (m.data[9] * m.data[2] - m.data[1] * m.data[10]) * det;
	data[5] = (-m.data[8] * m.data[2] + m.data[0] * m.data[10]) * det;
	data[9] = (m.data[8] * m.data[1] - m.data[0] * m.data[9] * m.data[15]) * det;
	data[2] = (-m.data[5] * m.data[2] + m.data[1] * m.data[6] * m.data[15]) * det;
	data[6] = (+m.data[4] * m.data[2] - m.data[0] * m.data[6] * m.data[15]) * det;
	data[10] = (-m.data[4] * m.data[1] + m.data[0] * m.data[5] * m.data[15]) * det;
	data[3] = (m.data[9] * m.data[6] * m.data[3]
		- m.data[5] * m.data[10] * m.data[3]
		- m.data[9] * m.data[2] * m.data[7]
		+ m.data[1] * m.data[10] * m.data[7]
		+ m.data[5] * m.data[2] * m.data[11]
		- m.data[1] * m.data[6] * m.data[11]) * det;
	data[7] = (-m.data[8] * m.data[6] * m.data[3]
		+ m.data[4] * m.data[10] * m.data[3]
		+ m.data[8] * m.data[2] * m.data[7]
		- m.data[0] * m.data[10] * m.data[7]
		- m.data[4] * m.data[2] * m.data[11]
		+ m.data[0] * m.data[6] * m.data[11]) * det;
	data[11] = (m.data[8] * m.data[5] * m.data[3]
		- m.data[4] * m.data[9] * m.data[3]
		- m.data[8] * m.data[1] * m.data[7]
		+ m.data[0] * m.data[9] * m.data[7]
		+ m.data[4] * m.data[1] * m.data[11]
		- m.data[0] * m.data[5] * m.data[11]) * det;
}
