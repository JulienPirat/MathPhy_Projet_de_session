#include "PhysicEngine.h"
#include <ParticleContactNaïve.h>
#include <ParticleContactResting.h>
#include <ParticleGravity.h>
#include <ParticleDrag.h>
#include <ParticleAnchoredSpring.h>
#include <ParticleBuoyancy.h>
#include <ParticleCable.h>
#include <ParticleRod.h>

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
		if (limitIterContactResolver < contactRegistry->Contacts.size() - 1) {
			//If we have more than "limitIterContactResolver" contacts to resolve we only solve "limitIterContactResolver" of them
			resolver.setIterations(limitIterContactResolver);
			resolver.resolveContacts(contactRegistry, limitIterContactResolver, deltaTime);
		}
		else {
			//We can resolve all contact this frame
			resolver.setIterations(contactRegistry->Contacts.size());
			resolver.resolveContacts(contactRegistry, contactRegistry->Contacts.size(), deltaTime);
		}
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
		forceRegistry_Particle.add(p, new ParticleDrag(100.f, 100.f));
	}
}

void PhysicEngine::putAnchoredSpringToParticle() {
	Vector3D* VOrigine = new Vector3D(0,0,0);
	for (auto p : this->particles) {
		forceRegistry_Particle.add(p, new ParticleAnchoredSpring(*VOrigine, 0.01f, 0.1f));
	}
}

void PhysicEngine::putBuoyancyToParticle() {

	for (auto p : this->particles) {
		forceRegistry_Particle.add(p,
			new ParticleBuoyancy(
				-30.f, //MaxDepth
				33.51f, //Particle volume V = 4/3 pi r3 and r=2
				-1.0f, //WaterHeight
				2.f //Water density (1000kg per m3)
			));
	}
}

void PhysicEngine::AddCableExample(Particle* part1, Particle* part2) {
	AdditionnalContactGeneratorRegistry.push_back(new ParticleCable(4,0.5f, part1, part2));
	//forceRegistry_Particle.add(part1, new ParticleGravity());

}

void PhysicEngine::AddRodExample(Particle* part1, Particle* part2) {
	AdditionnalContactGeneratorRegistry.push_back(new ParticleRod(3,part1,part2));
	//forceRegistry_Particle.add(part1, new ParticleGravity());

}

void PhysicEngine::CallAllContactGenerator()
{
	//Clear Basics for this frame
	for (auto c : BasicsContactGeneratorRegistry)
	{
		delete c;
	}
	
	BasicsContactGeneratorRegistry.clear();
	contactRegistry->ClearContactRegistry();

	//Initialisation of Basics Contact Generator
	BasicsContactGeneratorRegistry.push_back(new ParticleContactNaïve(0.5f, particles));
	BasicsContactGeneratorRegistry.push_back(new ParticleContactResting(2, particles));

	//On appelle le addContact sur le générateurs de contact basiques (Naive, Wall, Resting, ...)
	for (auto* bcontactgen : BasicsContactGeneratorRegistry) {
		bcontactgen->addContact(contactRegistry, limitIterContactGenerator);
	}

	//On appelle le addContact sur le générateurs de contact additionnels (Cable, Rod, ...)
	for (auto* acontactgen : AdditionnalContactGeneratorRegistry) {
		acontactgen->addContact(contactRegistry, limitIterContactGenerator);
	}
}
