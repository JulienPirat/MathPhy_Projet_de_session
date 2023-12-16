#include "Sphere.h"

Sphere::Sphere():RigidBody(MakeInverseInertiaSphere(1,1))
{
	shape = sphere;
	dimension = Vector3D(1, 0, 0);
}

Sphere::Sphere(Vector3D pos, Vector3D vel, Vector3D rotat, float linDamp, float angDamp, float mass, Color col, float radius) : RigidBody(pos, vel, rotat, linDamp, angDamp, mass, col, MakeInverseInertiaSphere(radius,mass), sphere, Vector3D(radius, 0, 0))
{
}

Matrix3 Sphere::MakeInverseInertiaSphere(float rad, float mass)
{
	Matrix3 I = Matrix3(
		(0.4) * (mass) * (rad), 0, 0,
		0, (0.4) * (mass) * (rad), 0,
		0, 0, (0.4) * (mass) * (rad)
	);
	return I.Inverse();
}
