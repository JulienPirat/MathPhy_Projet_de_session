#include "Plane.h"

Plane::Plane() : RigidBody(MakeInverseInertiaPlane(1, 1, 1))
{
	shape = plane;
	dimension = Vector3D(1, 1, 0);
}

Plane::Plane(Vector3D pos, Vector3D vel, Vector3D rotat, float linDamp, float angDamp, float mass, Color col, float x, float y) : RigidBody(pos, vel, rotat, linDamp, angDamp, mass, col, MakeInverseInertiaPlane(x,y,mass))
{
	shape = plane;
	dimension = Vector3D(x, y, 0);
}

Matrix3 Plane::MakeInverseInertiaPlane(double x, double y, double mass)
{
	Matrix3 I = Matrix3(
		(0.3333) * (mass) * (y * y), 0, 0, //Y = centre a un bord
		0, (0.3333) * (mass) * (x * x), 0, //X = centre a un bord
		0, 0, (0.333) * (mass) * (x * x + y * y)
	);
	return I.Inverse();
}
