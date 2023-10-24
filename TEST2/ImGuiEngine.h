#pragma once

struct GLFWwindow;

class ImGuiEngine
{
private:

	///Attributs

	GLFWwindow* window = nullptr;

	bool show_demo_window = true;
	bool show_another_window = false;

	bool visible = true;

	int lastState_Key_I = 0;

public:

	///Methodes

	bool Init(GLFWwindow* _window);

	void Update();
	void Render();
	void Shutdown();

	void processInput(GLFWwindow* window);
	void SetVisible(bool _visible);
};