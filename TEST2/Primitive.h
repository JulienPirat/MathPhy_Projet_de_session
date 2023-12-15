#pragma once
#include <Matrix4.h>

class RigidBody;

class Primitive {

public:
	
	//Constructor
	Primitive(RigidBody* RB, Matrix4 offset) : RB(RB), offset(offset) {}

	RigidBody* RB;
	Matrix4 offset;
};