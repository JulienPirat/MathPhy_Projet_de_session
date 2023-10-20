#include "world.h"
#include <GLFW/glfw3.h>

void World::AddParticle(Particle* particle)
{
	this->particles.push_back(particle);
}

int World::Run()
{
	auto res = this->Init();

	if (res == 1) return res;

	float lastTime = glfwGetTime();
	float currentTime = 0;
	float deltaT = 0;

    while (!graphics.ShouldClose())
    {
		currentTime = glfwGetTime();
		deltaT = currentTime - lastTime;
		lastTime = currentTime;

		this->Update(deltaT);
    }

	this->Shutdown();

	return 0;
}

int World::Init()
{
	graphics = GraphicEngine();
	GLFWwindow* window = graphics.Init();

	if (window == nullptr)
		return 1;

	imGui = ImGuiEngine();
	imGui.Init(window);

	physics.Init();

	imGui.SetVisible(true);

	return 0;
}

void World::Update(float deltaTime)
{
	physics.Update(deltaTime);

	graphics.Update();

	imGui.Update();

	graphics.Render(particles);

	imGui.Render();

	graphics.SwapBuffers();
}

void World::Shutdown()
{
    imGui.Shutdown();
    graphics.Shutdown();
}
