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
			double r;
			/**
			* Holds the first complex component of the quaternion.
			*/
			double i;
			/**
			* Holds the second complex component of the quaternion.
			*/
			double j;
			/**
			* Holds the third complex component of the quaternion.
			*/
			double k;
		};
			/**
			* Holds the quaternion data in array form.
			*/
			double data[4];
	};

	///Constructeur

	Quaternion(){
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;
	}
	Quaternion(double qr, double qi, double qj, double qk) {
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
	void rotateByVector(Vector3D& vector, double scale);

	//Apply the quaternion update the angular velocity
	void UpdateByAngularVelocity(Vector3D& rotation, float duration);

	friend bool operator==(const Quaternion& l, const Quaternion& r) {
		return l.r == r.r && l.i == r.i && l.j == r.j && l.k == r.k;
	}

};

