#include "PhysicEngine.h"
#include <ParticleContactNa�ve.h>

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

	GestionCollisions(); //Dois le faire avant le Integrate ???
}

void PhysicEngine::Shutdown()
{
	for (auto& p : particles)
	{
		delete p;
	}

	particles.clear();
}

void PhysicEngine::GestionCollisions()
{
	ParticleContactNa�ve* GCNaive = new ParticleContactNa�ve();
	GCNaive->particle = this->particles;
	GCNaive->radius = 1.0f;
	GCNaive->Init();

	
}
