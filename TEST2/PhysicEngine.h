#pragma once
#include <list>
#include <Particle.h>
#include <vector>
#include <ParticleContactResolver.h>
#include <ParticleContactGenerator.h>
#include <ParticleForceRegistry.h>
#include <ParticleContactRegistry.h>
#include <RBForceRegistry.h>
#include <RBGravityForceGenerator.h>
#include <RBSpringForceGenerator.h>
#include <RBAnchoredSpringForceGenerator.h>
#include <RBContactRegistry.h>
#include <RBContactGenerator.h>


class PhysicEngine
{
	public:

		///Constructeur

		PhysicEngine(std::vector<Particle*>& listParticles, std::vector<RigidBody*>& listRigidBody) : particles(listParticles), rigidbodies(listRigidBody) {};
		PhysicEngine();

		///Methodes

		void Init();

		void Update(float deltaTime);

		void Shutdown();

		void ClearParticles();

		void ClearRigidBodies();

		void putGravityToParticle();

		void putDragToParticle();

		void putAnchoredSpringToParticle();

		void putBuoyancyToParticle();

		void putGravityToRigidBody();

		void putSpringForTwoRigidBody(RigidBody* rb1, RigidBody* rb2);

		void putSpringForRigidBody(RigidBody* rb1, Vector3D WorldPoint);

		void AddCableExample(Particle* part1, Particle* part2);

		void AddRodExample(Particle* part1, Particle* part2);

		void CallAllContactGenerator();

		void CallRBContactGenerator();

		void AddContactBoxBox(RigidBody* rb1, RigidBody* rb2);

	private:

		///Attributs

		std::vector<RigidBody*>& rigidbodies;
		RBForceRegistry forceRegistry_Rigibody;

		std::vector<Particle*>& particles;
		ParticleForceRegistry forceRegistry_Particle;

		//Holds the list of contact generators.
		ParticleContactRegistry* contactRegistry = new ParticleContactRegistry();

		RBContactRegistry* contactRegistry_RigidBody = new RBContactRegistry();

		RBContactGenerator* contactGenerator = new RBContactGenerator();

		//Contact Generator Lists
		std::vector<ParticleContactGenerator*> BasicsContactGeneratorRegistry;
		std::vector<ParticleContactGenerator*> AdditionnalContactGeneratorRegistry;

		unsigned int limitIterContactGenerator = 100;
		unsigned int limitIterContactResolver = 10;
		
		//Holds the list of contacts.
		ParticleContact* contacts;

		//max number of contacts
		unsigned maxContacts;

		//contact resolver
		ParticleContactResolver resolver;
};

