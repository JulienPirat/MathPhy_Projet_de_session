#include "ParticleForceRegistry.h"

void ParticleForceRegistry::Add(Particle* particle, ParticleForceGenerator* forceGenerator)
{
	m_registery.push_back({ particle, forceGenerator });
}

void ParticleForceRegistry::Remove(Particle* particle, ParticleForceGenerator* forceGenerator)
{
	std::remove_if(m_registery.begin(), m_registery.end(), [particle, forceGenerator](ParticleForceRegistration entry) {
		return entry.particle == particle && entry.forceGenerator == forceGenerator;
	});
}

void ParticleForceRegistry::Clear()
{
	m_registery.clear();
}

void ParticleForceRegistry::UpdateForce(float duration)
{
	for(ParticleForceRegistration entry : m_registery)
	{
		entry.forceGenerator->UpdateForce(entry.particle, duration);
	}
}
