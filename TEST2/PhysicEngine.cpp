#include "PhysicEngine.h"
#include <ParticleContactNaïve.h>

void PhysicEngine::Init()
{
	//Nothing to do here since we've moved the initialization of particles into world
}

void PhysicEngine::Update(float deltaTime)
{

	//update the positions particles
	for (auto p : particles)
	{
		p->Integrate(deltaTime);
	}

	//Check Particules collisions
	GestionCollisions();
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
	//On récup toutes les particules du jeu
	GCNaive->particle = this->particles;
	//Boite de collision de toutes les particules
	GCNaive->radius = 1.0f;
	//
	GCNaive->Init();

	
}
