#include "PhysicEngine.h"
#include <ParticleContactNaïve.h>
#include <ParticleContactResting.h>
#include <ParticleGravity.h>
#include <ParticleDrag.h>
#include <ParticleAnchoredSpring.h>

void PhysicEngine::Init()
{

	//Nota bene : Additionnal Contact Generator is filled by the user

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

	//Check Particules collisions & fill contact list
	CallAllContactGenerator();

	//Resolve Contacts
	if (contactRegistry->Contacts.size() > 0) {
		resolver.setIterations(contactRegistry->Contacts.size()-1);
		resolver.resolveContacts(contactRegistry, contactRegistry->Contacts.size() - 1, deltaTime);
	}

	// Generate contacts.
	//unsigned usedContacts = generateContacts();

	// And process them.
	//resolver.setIterations(usedContacts * 2);
	//resolver.resolveContacts(contacts, usedContacts, deltaTime);
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
	//Clear Basics for this frame
	BasicsContactGeneratorRegistry.clear();

	//On appelle le addContact sur le générateurs de contact basiques (Naive, Wall, Resting, ...)

	//Initialisation of Basics Contact Generator
	BasicsContactGeneratorRegistry.push_back(new ParticleContactNaïve(2, particles));
	BasicsContactGeneratorRegistry.push_back(new ParticleContactResting(2, particles));

	for (auto* bcontactgen : BasicsContactGeneratorRegistry) {
		bcontactgen->addContact(contactRegistry, limitIterContactGenerator);
	}

	//On appelle le addContact sur le générateurs de contact additionnels (Cable, Rod, ...)
	for (auto* acontactgen : AdditionnalContactGeneratorRegistry) {
		acontactgen->addContact(contactRegistry, limitIterContactGenerator);
	}
}
