#include "PhysicEngine.h"
#include <ParticleContactNa�ve.h>
#include <ParticleContactResting.h>
#include <ParticleGravity.h>

void PhysicEngine::Init()
{
	//Nothing to do here since we've moved the initialization of particles into world
}

void PhysicEngine::Update(float deltaTime)
{

	//update the positions particles
	for (auto p : particles)
	{
		p->Integrate(deltaTime);
		p->isResting = false;
	}

	// Accumulation des forces
	// POURQUOI <-- ne pas supprimer c'est pour me retrouver
	forceRegistry_Particle.UpdateForce(deltaTime);

	//Check Particules collisions
	GestionCollisions(deltaTime);

	// Generate contacts.
	unsigned usedContacts = generateContacts();

	// And process them.
	resolver.setIterations(usedContacts * 2);
	resolver.resolveContacts(contacts, usedContacts, deltaTime);
}

void PhysicEngine::Shutdown()
{
	for (auto& p : particles)
	{
		delete p;
	}

	particles.clear();
}

void PhysicEngine::GestionCollisions(float deltaTime)
{
	
	ParticleContactResting* GCResting = new ParticleContactResting();
	//On r�cup toutes les particules du jeu
	GCResting->particle = this->particles;
	//Boite de collision de toutes les particules
	GCResting->radius = 0.5f;
	//
	GCResting->Init(deltaTime);
	
	ParticleContactNa�ve* GCNaive = new ParticleContactNa�ve();
	//On r�cup toutes les particules du jeu
	GCNaive->particle = this->particles;
	//Boite de collision de toutes les particules
	GCNaive->radius = 0.5f;
	//
	GCNaive->Init(deltaTime);
}

void PhysicEngine::putGravityToParticle()
{
	for (auto p : this->particles) {
		forceRegistry_Particle.add(p, new ParticleGravity());
	}
}

unsigned PhysicEngine::generateContacts()
{
	unsigned limit = maxContacts;
	ParticleContact* nextContact = contacts;
	ContactGenRegistration* reg = firstContactGen;
	while (reg)
	{
		unsigned used = reg->gen->addContact(nextContact, limit);
		limit -= used;
		nextContact += used;
		// We�ve run out of contacts to fill. This means we�re missing
		// contacts.
		if (limit <= 0) break;
		reg = reg->next;
	}
	// Return the number of contacts used.
	return maxContacts - limit;
}
