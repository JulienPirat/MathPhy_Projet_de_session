#pragma once
#include <RigidBody.h>

class RBForceGenerator {

public:
	//Apply force to the rigidBody
	virtual void UpdateForce(RigidBody* rigidBody) = 0;
};