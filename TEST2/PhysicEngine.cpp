#include "PhysicEngine.h"
#include <GLFW\glfw3.h>

void PhysicEngine::Init()
{
	particles = new std::list<Particle>();

	//fill the list with 10 particles with random properties
	for (int i = 0; i < 10; i++)
	{
		Particle p = Particle(
			Vector3D(rand() % 10, rand() % 10, rand() % 10), 
			Vector3D(rand() % 10, rand() % 10, rand() % 10), 
			Vector3D(rand() % 10, rand() % 10, rand() % 10), 
			(rand() % 10) * 1.0,
			(rand() % 10) * 1.0,
			Vector3D(rand() % 10, rand() % 10, rand() % 10)
		);
		particles->push_back(p);
	}

	lastTime = glfwGetTime();
}

void PhysicEngine::Update()
{
	//calculate the time between frames
	float currentFrame = glfwGetTime();
	float deltaT = currentFrame - lastTime;

	//update the particles
	for (std::list<Particle>::iterator it = particles->begin(); it != particles->end(); ++it)
	{
		it->Integrate(deltaT);
	}
}

void PhysicEngine::Shutdown()
{
		delete particles;
}

std::list<Particle>& PhysicEngine::GetParticles() const
{
	return *particles;
}
