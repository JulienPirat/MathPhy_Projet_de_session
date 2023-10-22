#pragma once
#include <list>
#include <Particle.h>
#include <LearnOpenGL\shader_m.h>
#include <vector>

struct GLFWwindow;

class GraphicEngine
{
public:

	GLFWwindow* Init();

	bool ShouldClose() const;

	void Update();

    void Render(std::vector<Particle*> const& particles);

	void SwapBuffers();

	void Shutdown();

private:
	GLFWwindow* window = nullptr;

    Shader* ourShader = nullptr;

	void RenderCube();
};