#include "PhysicEngine.h"
#include <GLFW\glfw3.h>

void PhysicEngine::Init()
{
	particles = std::list<Particle*>();

	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		Particle* p = new Particle(
			Vector3D(0, 0, 0),
			Vector3D(
				((double)(rand() % 2) / (double)RAND_MAX) - 1, 
				((double)(rand() % 2) / (double)RAND_MAX) - 1, 
				((double)(rand() % 2) / (double)RAND_MAX) - 1
			),
			Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX)),
			((double)rand() / (double)RAND_MAX),
			((double)rand() / (double)RAND_MAX),
			Vector3D(((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX), ((double)rand() / (double)RAND_MAX))
		);

		std::cout << "Particle " << i << " : "
			<< p->getPosition().x << " " << p->getPosition().y << " " << p->getPosition().z << std::endl
			<< p->getVelocity().x << " " << p->getVelocity().y << " " << p->getVelocity().z << std::endl
			<< p->getAcceleration().x << " " << p->getAcceleration().y << " " << p->getAcceleration().z << std::endl;

		particles.push_back(p);
	}

	lastTime = glfwGetTime();
}

void PhysicEngine::Update()
{
	//calculate the time between frames
	float currentFrame = glfwGetTime();
	float deltaT = currentFrame - lastTime;

	//update the particles
	for (auto p : particles)
	{
		p->Integrate(deltaT);
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

std::list<Particle*> PhysicEngine::GetParticles() const
{
	return particles;
}
