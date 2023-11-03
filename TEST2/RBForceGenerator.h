#pragma once
#include <RigidBody.h>

class RBForceGenerator {

public:
	//Apply forcce to the rigidBody
	virtual void UpdateForce(RigidBody* rigidBody) = 0;
};