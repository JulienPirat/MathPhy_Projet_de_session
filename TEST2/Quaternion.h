#pragma once
#include <math.h>
#include <Vector3D.h>

/**
* Holds a three degree of freedom orientation.
*/

class Quaternion
{
public:

	union {
		struct {
			/**
			* Holds the real component of the quaternion.
			*/
			float r;
			/**
			* Holds the first complex component of the quaternion.
			*/
			float i;
			/**
			* Holds the second complex component of the quaternion.
			*/
			float j;
			/**
			* Holds the third complex component of the quaternion.
			*/
			float k;
		};
			/**
			* Holds the quaternion data in array form.
			*/
			float data[4];
	};



	///Constructeur

	Quaternion(float qr, float qi, float qj, float qk) {
		data[0] = qr;
		data[1] = qi;
		data[2] = qj;
		data[3] = qk;
	}

	/**
	* Normalizes the quaternion to unit length, making it a valid
	* orientation quaternion.
	*/
	void normalize()
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

	/**
	* Multiplies the quaternion by the given quaternion.
	*
	* @param multiplier The quaternion by which to multiply.
	*/
	void operator *=(const Quaternion& multiplier)
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

	/*
	void rotateByVector(constVector& vector)
	{
		Quaternion q(0, 
			vector.x * scale, 
			vector.y * scale,
			vector.z * scale);
		(*this) *= q;
	}
	*/

	//BENJ METHOD REDONE
	void rotateByVector(Vector3D& vector, float scale)
	{
		Quaternion q(0,
			vector.x * scale,
			vector.y * scale,
			vector.z * scale);
		(*this) *= q;
	}

	/**
	* Adds the given vector to this, scaled by the given amount.
	* This is used to update the orientation quaternion by a rotation
	* and time.
	*
	* @param vector The vector to add.
	*
	* @param scale The amount of the vector to add.
	*/
	void addScaledVector(const Vector3D& vector, float scale)
	{
		Quaternion q(0,
			vector.x * scale,
			vector.y * scale,
			vector.z * scale);
		q *= *this;
		r += q.r * ((float)0.5);
		i += q.i * ((float)0.5);
		j += q.j * ((float)0.5);
		k += q.k * ((float)0.5);
	}
};

