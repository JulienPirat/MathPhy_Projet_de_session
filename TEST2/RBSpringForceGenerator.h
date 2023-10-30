#include "RBForceGenerator.h"

class RBSpringForceGenerator : public RBForceGenerator {

private:

	// Anchor point in Local coordinate
	Vector3D m_bodyAnchor;

	// Other anchor point in other's Local coordinate
	Vector3D m_otherBodyAnchor;

	RigidBody* m_otherRigidBody = nullptr;

	// spring parameters
	float m_k;
	float m_restLenght;

public:
	// Transform each anchor point in world coordinate,
	// calculate the spring force and apply it at anchor point.
	void UpdateForce(RigidBody* rigidBody);
};