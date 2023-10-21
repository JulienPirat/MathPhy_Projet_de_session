#include "PhysicEngine.h"
#include <ParticleContactNaïve.h>

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
	ParticleContactNaïve* GCNaive = new ParticleContactNaïve();
	GCNaive->particle = this->particles;
	GCNaive->radius = 1.0f;
	GCNaive->Init();

	
}
