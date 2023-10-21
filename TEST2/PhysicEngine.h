#pragma once
#include <list>
#include <Particle.h>
#include <vector>

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
};

