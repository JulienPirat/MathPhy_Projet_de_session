#pragma once

struct GLFWwindow;

class GraphicEngine
{
public:
	GLFWwindow* Init();

	bool ShouldClose() const;

	void Update();

	void Render();

	void SwapBuffers();

	void Shutdown();

private:
	GLFWwindow* window = nullptr;
};