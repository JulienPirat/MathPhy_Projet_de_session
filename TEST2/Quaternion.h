#pragma once
#include <math.h>
#include <Vector3D.h>


class Quaternion
{
public:

	///Structure

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

	Quaternion(){
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;
	}
	Quaternion(float qr, float qi, float qj, float qk) {
		data[0] = qr;
		data[1] = qi;
		data[2] = qj;
		data[3] = qk;
	}

	//Normalized by multiplying the quaternion by the inverse of its magnitude
	void Normalized();

	//Quaternion Multiplication
	void operator *=(const Quaternion& multiplier);

	//Rotate the quaternion by a vector - multiply this by q = (0, dx, dy, dz)
	void rotateByVector(Vector3D& vector, float scale);

	//Apply the quaternion update the angular velocity
	void UpdateByAngularVelocity(Vector3D& rotation, float duration);

};

