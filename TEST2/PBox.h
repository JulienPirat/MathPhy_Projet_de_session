#pragma once
#include "Primitive.h"
#include <vector>
class RigidBody;


class PBox : public Primitive {
public:

	//Constructor
	PBox(RigidBody* RB, Matrix4 offset, Vector3D halfsize) : Primitive( RB, offset) {
		//RB->dimension/2
		halfSize = halfsize;
	}

	Vector3D halfSize;

	/// <summary>
	/// Return the vertices of the box
	/// </summary>
	/// <returns></returns>
	std::vector<Vector3D> GetVertices();
};