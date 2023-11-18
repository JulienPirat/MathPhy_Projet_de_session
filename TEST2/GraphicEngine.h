#pragma once
#include <list>
#include <Particle.h>
#include <LearnOpenGL\shader_m.h>
#include <vector>
#include <RigidBody.h>

struct GLFWwindow;

class GraphicEngine
{
public:

	///Methodes

	GLFWwindow* Init();

	bool ShouldClose() const;

	void Update();

    void Render(std::vector<Particle*> const& particles, std::vector<RigidBody*> const& bodies);

	void SwapBuffers();

	void Shutdown();

private:

	///Attributs

	GLFWwindow* window = nullptr;

    Shader* ourShader = nullptr;

	void RenderCube(Vector3D topPosition, Vector3D bottomPosition, RigidBody* b);
	void RenderSphere(Vector3D position);

	unsigned int VBO, VAO;
};