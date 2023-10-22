#pragma once
#include <GraphicEngine.h>
#include <PhysicEngine.h>
#include <ImGuiEngine.h>
#include <vector>
#include <ParticleContactResolver.h>
#include <ParticleContactGenerator.h>

class World
{
public:
	void AddParticle(Particle* particle);
	void GenBasicCollision();
	int Run();

private :
	GraphicEngine graphics;
	PhysicEngine physics = PhysicEngine(particles);
	ImGuiEngine imGui;

	ParticleContactResolver contactResolver = ParticleContactResolver(10);

	std::vector<Particle*> particles = std::vector<Particle*>();

	int Init();
	void Update(float deltaTime);
	void Shutdown();
};

