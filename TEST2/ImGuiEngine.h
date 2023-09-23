#pragma once

struct GLFWwindow;

class ImGuiEngine
{
private:
	GLFWwindow* window = nullptr;

	bool show_demo_window = true;
	bool show_another_window = false;

public:
	bool Init(GLFWwindow* _window);

	void Update();
	void Render();
	void Shutdown();
};