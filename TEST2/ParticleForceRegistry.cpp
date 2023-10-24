#include "ParticleForceRegistry.h"

/// <summary>
/// Ajoute un lien entre une particule et sont ForceGenerator dans le registre.
/// </summary>
/// <param name="particle"></param>
/// <param name="fg">ParticleForceGenerator</param>
void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg)
{
	ParticleForceEntry newParticleForceEntry = ParticleForceEntry();
	newParticleForceEntry.forceGenerator = fg;
	newParticleForceEntry.particle = particle;
	m_registery.push_back(newParticleForceEntry);
}

/// <summary>
/// Supprime un lien entre une particule et sont ForceGenerator dans le registre.
/// </summary>
/// <param name="particle"></param>
/// <param name="fg">ParticleForceGenerator</param>
void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg)
{
	Registry::iterator i = m_registery.begin();

	for (; i != m_registery.end(); i++) {
		if (i->particle == particle && i->forceGenerator == fg) {
			m_registery.erase(i);
			return; // Sortie de la boucle une fois que l'entr�e a �t� supprim�e.
		}
	}
}

/// <summary>
/// Supprime toutes les entr�es du registre li�es � leur syst�me de g�n�ration de force.
/// </summary>
void ParticleForceRegistry::clear()
{
	m_registery.clear();
}

/// <summary>
/// Toutes les particules enregistr�es avec un forceGenerator sont appel�es
/// pour update la force.
/// </summary>
/// <param name="duration">DeltaTime</param>
void ParticleForceRegistry::UpdateForce(float duration)
{
	Registry::iterator i = m_registery.begin();
	for (; i != m_registery.end(); i++) {
		i->forceGenerator->UpdateForce(i->particle, duration);
	}
}
