#include "RBSpringForceGenerator.h"

void RBSpringForceGenerator::UpdateForce(RigidBody* rigidBody)
{
	// Calculate the vector of the spring
	auto force = rigidBody->transformMatrix * m_bodyAnchor;
	if (m_otherRigidBody == nullptr) {
		force -= m_otherBodyAnchor;
	}
	else {
		force -= m_otherRigidBody->transformMatrix * m_otherBodyAnchor;
	}

	// Calculate the magnitude of the force
	float magnitude = force.magnitude();
	magnitude = fabs(magnitude - m_restLenght);
	magnitude *= m_k;

	// Calculate the final frce and apply it
	force.normalize();
	force *= -magnitude;
	if (!(force == (Vector3D(0, 0, 0)))) {
		if (m_bodyAnchor.operator==(Vector3D(0, 0, 0)) || m_otherBodyAnchor.operator==(Vector3D(0, 0, 0))) {
			// Si l'origine du ressort est égale a l'origine du rigidBody
			rigidBody->AddForce(force);
			force.x *= -1;
			force.y *= -1;
			force.z *= -1;
			m_otherRigidBody->AddForce(force);
		}
		else {
			rigidBody->AddForceAtBodyPoint(force, m_bodyAnchor);
			force.x *= -1;
			force.y *= -1;
			force.z *= -1;
			m_otherRigidBody->AddForceAtBodyPoint(force, m_otherBodyAnchor);
		}
	}
}
