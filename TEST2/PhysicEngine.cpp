#include "PhysicEngine.h"
#include <ParticleContactNa�ve.h>

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
	GestionCollisions(deltaTime);
}

void PhysicEngine::Shutdown()
{
	for (auto& p : particles)
	{
		delete p;
	}

	particles.clear();
}

void PhysicEngine::GestionCollisions(float deltaTime)
{
	ParticleContactNa�ve* GCNaive = new ParticleContactNa�ve();
	//On r�cup toutes les particules du jeu
	GCNaive->particle = this->particles;
	//Boite de collision de toutes les particules
	GCNaive->radius = 0.5f;
	//
	GCNaive->Init(deltaTime);

	
}
