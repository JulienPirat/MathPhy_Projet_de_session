#include "ParticleGravity.h"

void ParticleGravity::UpdateForce(Particle* particle, double duration)
{
	Vector3D newGravityForce = Vector3D(m_gravity.x * particle->getInverseMass(), m_gravity.y * particle->getInverseMass(), m_gravity.z * particle->getInverseMass());
	particle->addForce(newGravityForce);
}
