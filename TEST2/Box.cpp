#include "Box.h"

Box::Box():RigidBody(MakeInverseInertiaCuboide(Vector3D(1,1,1),1)){

}

Box::Box(Vector3D pos, Vector3D vel, Vector3D rotat, float linDamp, float angDamp, float mass, Vector3D col, Vector3D dim) : RigidBody(pos, vel, rotat, linDamp, angDamp, mass, col, MakeInverseInertiaCuboide(dim, mass)) {
	
}

Matrix3 Box::MakeInverseInertiaCuboide(Vector3D dim, float mass)
{
	Matrix3 I = Matrix3(
		(0.083) * (mass) * (dim.y * dim.y + dim.z * dim.z), 0, 0,
		0, (0.083) * (mass) * (dim.x * dim.x + dim.z * dim.z), 0,
		0, 0, (0.083) * (mass) * (dim.x * dim.x + dim.y * dim.y)
	);
	return I.Inverse();
}