#include "PhysicEngine.h"
#include <ParticleContactNaïve.h>
#include <ParticleContactResting.h>
#include <ParticleGravity.h>
#include <ParticleDrag.h>
#include <ParticleAnchoredSpring.h>
#include <ParticleBuoyancy.h>
#include <ParticleCable.h>
#include <ParticleRod.h>
#include <KDTRee.h>

void PhysicEngine::Init()
{

	//Nota bene : Additionnal Contact Generator is filled by the user

}

void PhysicEngine::Update(float deltaTime)
{
	Node* root = KDTRee::generateTree(0, rigidbodies, Axis::X);
	std::vector<std::pair<RigidBody*,RigidBody*>> potentialCollision = KDTRee::getPotentialCollisions(rigidbodies, root);
	//std::cout << potentialCollision.size() << std::endl;

	//update the positions particles
	for (auto p : particles)
	{
		p->Integrate(deltaTime);
		p->isResting = false;
	}

	//update rigidbodys positions 
	for (auto rb : rigidbodies)
	{
		rb->Integrate(deltaTime);
	}

	// Accumulation des forces
	forceRegistry_Particle.UpdateForce(deltaTime);
	forceRegistry_Rigibody.UpdateForce();

	// Check RigidBodies collisions
	//CallRBContactGenerator();


	//Check Particules collisions & fill contact list
	CallAllContactGenerator();

	//Resolve Particles Contacts
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

	//Resolve RB Contacts
	if (contactRegistry_RigidBody->contacts.size() > 0) {
		if (RBlimitIterContactResolver < contactRegistry_RigidBody->contacts.size() - 1) {
			//If we have more than "limitIterContactResolver" contacts to resolve we only solve "limitIterContactResolver" of them
			RBresolver.setIterations(RBlimitIterContactResolver);
			RBresolver.resolveContacts(contactRegistry_RigidBody, RBlimitIterContactResolver, deltaTime);
		}
		else {
			//We can resolve all contact this frame
			RBresolver.setIterations(contactRegistry_RigidBody->contacts.size());
			RBresolver.resolveContacts(contactRegistry_RigidBody, contactRegistry_RigidBody->contacts.size(), deltaTime);
		}
	}


	KDTRee::deleteTree(root);
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

void PhysicEngine::CallRBContactGenerator()
{
	contactRegistry_RigidBody->ClearContactRegistry();
}

void PhysicEngine::AddContactBoxBox(RigidBody* rb1, RigidBody* rb2)
{
	PBox* box1 = new PBox(rb1, rb1->transformMatrix);
	PBox* box2 = new PBox(rb2, rb2->transformMatrix);
	box1->halfSize = Vector3D(0.5, 0.5, 0.5);
	box2->halfSize = Vector3D(0.5, 0.5, 0.5);
	rb1->primitive = box1;
	rb2->primitive = box2;
	contactGenerator->boxAndBox(box1, box2, contactRegistry_RigidBody);
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

void PhysicEngine::ClearRigidBodies()
{
	for (auto& rb : rigidbodies)
	{
		delete rb;
	}

	rigidbodies.clear();
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

void PhysicEngine::putGravityToRigidBody()
{
	for (auto rb : this->rigidbodies) {
		forceRegistry_Rigibody.add(rb, new RBGravityForceGenerator());
	}
}

void PhysicEngine::putSpringForTwoRigidBody(RigidBody* rb1, RigidBody* rb2)
{
	forceRegistry_Rigibody.add(rb1, new RBSpringForceGenerator(Vector3D(-1 ,-1 ,1), Vector3D(1, -1, 1), 1, 50.0f, rb2));
}

void PhysicEngine::putSpringForRigidBody(RigidBody* rb1, Vector3D WorldPoint)
{
	forceRegistry_Rigibody.add(rb1, new RBAnchoredSpringForceGenerator(Vector3D(-5, -5, -5), WorldPoint, 1.0f, 3.0f));
}

void PhysicEngine::AddCableExample(Particle* part1, Particle* part2) {
	AdditionnalContactGeneratorRegistry.push_back(new ParticleCable(4,0.5f, part1, part2));
	//forceRegistry_Particle.add(part1, new ParticleGravity());

}

void PhysicEngine::AddRodExample(Particle* part1, Particle* part2) {
	AdditionnalContactGeneratorRegistry.push_back(new ParticleRod(3,part1,part2));
	//forceRegistry_Particle.add(part1, new ParticleGravity());

}
