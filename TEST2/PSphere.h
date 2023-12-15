#pragma once

#include "Primitive.h"

class PSphere : public Primitive {

public:
	
	PSphere(RigidBody* RB, Matrix4 offset) : Primitive(RB, offset) {};

	float radius = RB->dimension.x;

};
