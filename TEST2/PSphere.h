#pragma once

#include "Primitive.h"

class PSphere : public Primitive {

public:
	
	PSphere(float radius, RigidBody* RB, Matrix4 offset) : Primitive(RB, offset), radius(radius) {};

	float radius = RB->dimension.x;

};
