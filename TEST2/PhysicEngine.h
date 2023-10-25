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

		void GestionCollisions(float deltaTime);

		void putGravityToParticle();

		void putDragToParticle();

		void putAnchoredSpringToParticle();

		void CallAllContactGenerator();

	private:

		//generate contacts
		unsigned generateContacts();

		///Attributs

		std::vector<Particle*>& particles;

		ParticleForceRegistry forceRegistry_Particle;

		/*
		struct ContactGenRegistration
		{
			ParticleContactGenerator* gen;
			ContactGenRegistration* next;
		};

		//Holds the list of contact generators.
		ContactGenRegistration* firstContactGen;
		*/

		//Holds the list of contact generators.
		ParticleContactRegistry* contactRegistry;

		//Contact Generator Lists
		std::vector<ParticleContactGenerator*> BasicsContactGeneratorRegistry;
		std::vector<ParticleContactGenerator*> AdditionnalContactGeneratorRegistry;

		unsigned int limitIterContactGenerator = 10;
		
		//Holds the list of contacts.
		ParticleContact* contacts;

		//max number of contacts
		unsigned maxContacts;

		//contact resolver
		ParticleContactResolver resolver;
};

