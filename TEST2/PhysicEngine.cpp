#include "PhysicEngine.h"
#include <ParticleContactNaïve.h>
#include <ParticleContactResting.h>
#include <ParticleGravity.h>
#include <ParticleDrag.h>
#include <ParticleAnchoredSpring.h>

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
	ClearParticles();
}

void PhysicEngine::ClearParticles() {

	for (auto& p : particles)
	{
		delete p;
	}

	particles.clear();

}

void PhysicEngine::GestionCollisions(float deltaTime)
{
	/*
	ParticleContactResting* GCResting = new ParticleContactResting();
	//On récup toutes les particules du jeu
	GCResting->particle = this->particles;
	//Boite de collision de toutes les particules
	GCResting->radius = 0.5f;
	//
	GCResting->Init(deltaTime);
	
	ParticleContactNaïve* GCNaive = new ParticleContactNaïve();
	//On récup toutes les particules du jeu
	GCNaive->particle = this->particles;
	//Boite de collision de toutes les particules
	GCNaive->radius = 0.5f;
	//
	GCNaive->Init(deltaTime);
	*/
}

void PhysicEngine::putGravityToParticle()
{
	for (auto p : this->particles) {
		forceRegistry_Particle.add(p, new ParticleGravity());
	}
}

void PhysicEngine::putDragToParticle()
{
	for (auto p : this->particles) {
		forceRegistry_Particle.add(p, new ParticleDrag());
	}
}

void PhysicEngine::putAnchoredSpringToParticle() {
	Vector3D* VOrigine = new Vector3D(0,0,0);
	for (auto p : this->particles) {
		forceRegistry_Particle.add(p, new ParticleAnchoredSpring(*VOrigine, 0.01f, 0.1f));
	}
}

void PhysicEngine::CallAllContactGenerator()
{
	//On appelle le addContact sur le générateurs de contact basiques (Naive, Wall, Resting, ...)
	for (auto* bcontactgen : BasicsContactGeneratorRegistry) {
		bcontactgen->addContact(contactRegistry, 3);
	}

	for (auto* acontactgen : AdditionnalContactGeneratorRegistry) {
		acontactgen->addContact(contactRegistry, 3);
	}
}

unsigned PhysicEngine::generateContacts()
{
	unsigned limit = maxContacts;
	ParticleContact* nextContact = contacts;
	for (auto reg : contactRegistry)
	{
		unsigned used = reg->addContact(nextContact, limit);
		limit -= used;
		nextContact += used;
		// We’ve run out of contacts to fill. This means we’re missing
		// contacts.
		if (limit <= 0) break;
	}
	// Return the number of contacts used.
	return maxContacts - limit;
}
