#pragma once
#include <list>
#include <Particle.h>
class PhysicEngine
{
	public:
		void Init();

		void Update();

		void Shutdown();

		void GestionCollisions();

		std::list<Particle*> GetParticles() const;

	private:
		std::list<Particle*> particles;

		float lastTime = 0.0f;	// time between current frame and last frame
};

