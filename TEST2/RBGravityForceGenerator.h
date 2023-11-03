#include "RBForceGenerator.h"

class RBGravityForceGenerator : public RBForceGenerator {

private:
	Vector3D m_gravity = Vector3D(0, -10, 0);

public:
	// Apply the gravity force to center of mass of the rigidBody
	void UpdateForce(RigidBody* rigidBody);
};