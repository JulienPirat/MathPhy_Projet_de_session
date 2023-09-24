#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

struct GLFWwindow;

class CameraController {

private:
	GLFWwindow* window = nullptr;

public:
	void Init(GLFWwindow* _window);

	void Update();
	void Shutdown();
};