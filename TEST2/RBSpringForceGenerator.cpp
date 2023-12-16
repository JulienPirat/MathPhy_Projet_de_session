#include "RBSpringForceGenerator.h"

void RBSpringForceGenerator::UpdateForce(RigidBody* rigidBody)
{
	// Calculate the vector of the spring
	auto force = rigidBody->transformMatrix * m_bodyAnchor;
	force -= m_otherRigidBody->transformMatrix * m_otherBodyAnchor;

	// Calculate the magnitude of the force
	float magnitude = force.magnitude();
	magnitude = fabs(magnitude - m_restLenght);
	magnitude *= m_k;

	// Calculate the final frce and apply it
	force.normalize();
	force *= -magnitude;
	if (!(force == (Vector3D(0, 0, 0)))) {

		if (m_bodyAnchor == Vector3D(0, 0, 0)) {
			rigidBody->AddForce(force);
		}
		else {
			rigidBody->AddForceAtBodyPoint(force, m_bodyAnchor);
		}

		force.x *= -1;
		force.y *= -1;
		force.z *= -1;

		if (m_otherBodyAnchor == Vector3D(0, 0, 0)) {
			m_otherRigidBody->AddForce(force);
		}
		else {
			m_otherRigidBody->AddForceAtBodyPoint(force, m_otherBodyAnchor);
		}
	}
}
