#pragma once
#include <list>
#include <Particle.h>
#include <vector>
#include <ParticleContactResolver.h>
#include <ParticleContactGenerator.h>
#include <ParticleForceRegistry.h>
#include <ParticleContactRegistry.h>

class PhysicEngine
{
	public:

		///Constructeur

		PhysicEngine(std::vector<Particle*>& listParticles) : particles(listParticles) {};
		PhysicEngine();

		///Methodes

		void Init();

		void Update(float deltaTime);

		void Shutdown();

		void ClearParticles();

		void putGravityToParticle();

		void putDragToParticle();

		void putAnchoredSpringToParticle();

		void putBuoyancyToParticle();

		void CallAllContactGenerator();

	private:

		///Attributs

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

