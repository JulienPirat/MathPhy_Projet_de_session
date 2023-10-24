#pragma once
#include <list>
#include <Particle.h>
#include <vector>
#include <ParticleContactResolver.h>
#include <ParticleContactGenerator.h>
#include <ParticleForceRegistry.h>

class PhysicEngine
{
	public:
		PhysicEngine(std::vector<Particle*>& listParticles) : particles(listParticles) {};
		PhysicEngine();

		void Init();

		void Update(float deltaTime);

		void Shutdown();

		void GestionCollisions(float deltaTime);



	private:
		std::vector<Particle*>& particles;

		ParticleForceRegistry forceRegistry_Particle;

		struct ContactGenRegistration
		{
			ParticleContactGenerator* gen;
			ContactGenRegistration* next;
		};

		//Holds the list of contact generators.
		ContactGenRegistration* firstContactGen;
		
		//Holds the list of contacts.
		ParticleContact* contacts;

		//max number of contacts
		unsigned maxContacts;

		//generate contacts
		unsigned generateContacts();

		//contact resolver
		ParticleContactResolver resolver;
};

