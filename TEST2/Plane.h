#pragma once
#include "RigidBody.h"


class Plane : public RigidBody
{
public:
	Plane();
	Plane(Vector3D pos, Vector3D vel, Vector3D rotat, float linDamp, float angDamp, float mass, Vector3D col, float x, float y);
private:
	Matrix3 MakeInverseInertiaPlane(float x, float y, float mass);
};

