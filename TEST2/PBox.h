#pragma once
#include "Primitive.h"
#include <vector>


class PBox : public Primitive {
public:
	Vector3D halfSize;

	/// <summary>
	/// Return the vertices of the box
	/// </summary>
	/// <returns></returns>
	std::vector<Vector3D> GetVertices();
};