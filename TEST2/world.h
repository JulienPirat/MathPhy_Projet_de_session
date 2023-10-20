#pragma once
#include <GraphicEngine.h>
#include <PhysicEngine.h>
#include <ImGuiEngine.h>
#include <vector>

class World
{
public:
	World();
	~World();

	void AddParticle(Particle* particle);
	int Run();

private :
	GraphicEngine graphics;
	PhysicEngine physics = PhysicEngine(particles);
	ImGuiEngine imGui;

	std::vector<Particle*> particles = std::vector<Particle*>();

	int Init();
	void Update(float deltaTime);
	void Shutdown();
};

