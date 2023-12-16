#pragma once

struct GLFWwindow;

class ImGuiEngine
{
private:

	///Attributs

	GLFWwindow* window = nullptr;

	int window_to_show = 0;

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