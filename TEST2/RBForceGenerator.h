#pragma once
#include <RigidBody.h>

class RBForceGenerator {

public:
	//Apply forcce to the rigidBody
	virtual void updateForce(RigidBody* rigidBody) = 0;
};