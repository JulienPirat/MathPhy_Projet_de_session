#pragma once
#include "RigidBody.h"


class Sphere : public RigidBody
{
public:
	Sphere();
	Sphere(Vector3D pos, Vector3D vel, Vector3D rotat, float linDamp, float angDamp, float mass, Color col, float radius);
private:
	Matrix3 MakeInverseInertiaSphere(float rad, float mass);
};

