#pragma once
#include "Primitive.h"
#include "Vector3D.h"

class PPlane : public Primitive {
public:
	Vector3D normal;
	float offset;
};