#include "PhysicEngine.h"

void PhysicEngine::Init()
{
	//Nothing to do here since we've moved the initialization of particles into world
}

void PhysicEngine::Update(float deltaTime)
{
	//update the particles
	for (auto p : particles)
	{
		p->Integrate(deltaTime);
	}
}

void PhysicEngine::Shutdown()
{
	for (auto& p : particles)
	{
		delete p;
	}

	particles.clear();
}
