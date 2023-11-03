#include "RBForceRegistry.h"

void RBForceRegistry::add(RigidBody* rigidbody, RBForceGenerator* fg)
{
	m_registery.push_back({ rigidbody, fg });
}

void RBForceRegistry::remove(RigidBody* rigidbody, RBForceGenerator* fg)
{
	Registry::iterator i = m_registery.begin();

	for (; i != m_registery.end(); i++) {
		if (i->rigidbody == rigidbody && i->RBforceGenerator == fg) {
			m_registery.erase(i);
			return; // Sortie de la boucle une fois que l'entrée a été supprimée.
		}
	}
}

void RBForceRegistry::clear()
{
	m_registery.clear();
}

void RBForceRegistry::UpdateForce()
{
	Registry::iterator i = m_registery.begin();
	for (; i != m_registery.end(); i++) {
		i->RBforceGenerator->updateForce(i->rigidbody);
	}
}
