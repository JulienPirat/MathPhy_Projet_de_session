#include "RBForceGenerator.h"

class RBSpringForceGenerator : public RBForceGenerator {

private:
	// Anchor point in Local coordinate
	Vector3D m_bodyAnchor;

	RigidBody* m_otherRigidBody = nullptr;
	// Other anchor point in other's Local coordinate
	Vector3D m_otherBodyAnchor;

	// spring parameters
	float m_k;
	float m_restiLenght;

public:
	// Transform each anchor point in world coordinate,
	// calculate the spring froce and apply it at anchor point.
	void UpdateForce(RigidBody* rigidBody);
};