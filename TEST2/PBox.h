#pragma once
#include "Primitive.h"
#include <vector>


class PBox : public Primitive {
public:

	//Constructor
	PBox(RigidBody* RB, Matrix4 offset) : Primitive( RB, offset) {}

	Vector3D halfSize;

	/// <summary>
	/// Return the vertices of the box
	/// </summary>
	/// <returns></returns>
	std::vector<Vector3D> GetVertices();
};