#pragma once

#include "Primitive.h"
class RigidBody;

class PSphere : public Primitive {

public:
	
	PSphere(RigidBody* RB, Matrix4 offset, double rad) : Primitive(RB, offset) {
		//RB->dimension.x
		radius = rad;
	};

	double radius;

};
