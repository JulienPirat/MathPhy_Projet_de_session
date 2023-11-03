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

class PhysicEngine
{
	public:

		///Constructeur

		PhysicEngine(std::vector<Particle*>& listParticles, std::vector<RigidBody*>& listRigidBody) : particles(listParticles), rigidbodys(listRigidBody) {};
		PhysicEngine();

		///Methodes

		void Init();

		void Update(float deltaTime);

		void Shutdown();

		void ClearParticles();

		void ClearRigidBodys();

		void putGravityToParticle();

		void putDragToParticle();

		void putAnchoredSpringToParticle();

		void putBuoyancyToParticle();

		void putGravityToRigidBody();

		void AddCableExample(Particle* part1, Particle* part2);

		void AddRodExample(Particle* part1, Particle* part2);

		void CallAllContactGenerator();

	private:

		///Attributs

		std::vector<RigidBody*>& rigidbodys;
		RBForceRegistry forceRegistry_Rigibody;

		std::vector<Particle*>& particles;
		ParticleForceRegistry forceRegistry_Particle;

		//Holds the list of contact generators.
		ParticleContactRegistry* contactRegistry = new ParticleContactRegistry();

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

