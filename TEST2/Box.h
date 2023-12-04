#pragma once
#include "RigidBody.h"

class Box : public RigidBody
{
public:

	Box();
	Box(Vector3D pos, Vector3D vel, Vector3D rotat, float linDamp, float angDamp, float mass, Vector3D col, Vector3D dim);

private:

	Matrix3 MakeInverseInertiaCuboide(Vector3D dim, float mass);

};

