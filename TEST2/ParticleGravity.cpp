#include "ParticleGravity.h"

void ParticleGravity::UpdateForce(Particle* particle, float duration)
{
	// POURQUOI Pourquoi on a une duration ?

	Vector3D newGravityForce = Vector3D(m_gravity.x * particle->getInverseMass(), m_gravity.y * particle->getInverseMass(), m_gravity.z * particle->getInverseMass());
	particle->addForce(newGravityForce);
}
