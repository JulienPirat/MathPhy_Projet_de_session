#include "ParticleBuoyancy.h"

void ParticleBuoyancy::UpdateForce(Particle* particle, float duration)
{
	float depth = particle->getPosition().y;
	if (depth >= m_waterHeight + m_maxDepth)
		return;
	Vector3D force(0, 0, 0);
	if (depth <= m_waterHeight - m_maxDepth)
	{
		force.y = liquidDensity * m_volume;
		particle->addForce(force);
		return;
	}
	force.y = liquidDensity * m_volume * (depth - m_maxDepth - m_waterHeight) / 2 * m_maxDepth;
	particle->addForce(force);
}
