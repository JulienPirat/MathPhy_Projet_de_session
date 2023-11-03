#include "Quaternion.h"

void Quaternion::Normalized()
{
	float d = r * r + i * i + j * j + k * k;
	// Check for zero length quaternion, and use the no-rotation
	// quaternion in that case.
	if (d == 0) {
		r = 1;
		return;
	}d = ((float)1.0) / sqrtf(d);
	r *= d;
	i *= d;
	j *= d;
	k *= d;
}

void Quaternion::operator*=(const Quaternion& multiplier)
{
	Quaternion q = *this;
	r = q.r * multiplier.r - q.i * multiplier.i -
		q.j * multiplier.j - q.k * multiplier.k;
	i = q.r * multiplier.i + q.i * multiplier.r +
		q.j * multiplier.k - q.k * multiplier.j;
	j = q.r * multiplier.j + q.j * multiplier.r +
		q.k * multiplier.i - q.i * multiplier.k;
	k = q.r * multiplier.k + q.k * multiplier.r +
		q.i * multiplier.j - q.j * multiplier.i;
}

void Quaternion::rotateByVector(Vector3D& vector, float scale)
{
	Quaternion q(0,
		vector.x * scale,
		vector.y * scale,
		vector.z * scale);
	(*this) *= q;
}

void Quaternion::UpdateByAngularVelocity(Vector3D& rotation, float duration)
{
	//BENJ UNDERSTAND
	Quaternion q(0,
		rotation.x * duration,
		rotation.y * duration,
		rotation.z * duration);
	q *= *this;
	r += q.r * ((float)0.5);
	i += q.i * ((float)0.5);
	j += q.j * ((float)0.5);
	k += q.k * ((float)0.5);
}

