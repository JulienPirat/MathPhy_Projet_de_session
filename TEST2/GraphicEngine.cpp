#include "GraphicEngine.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>


float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

GLFWwindow* GraphicEngine::Init()
{


    //////////////////////////////////////////////////////////////////////////
    /////// CODE ENGINE
    ///////
    ///////

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return nullptr;

    // Create window with graphics context
    GLFWwindow* _window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    window = _window;

    if (window == nullptr)
        return window;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    //////////////////////////////////////////////////////////////////////////
    /////// CODE Camera.cpp
    ///////
    ///////


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    /////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////

    return window;
}

bool GraphicEngine::ShouldClose() const
{
    return window == nullptr || glfwWindowShouldClose(window);
}

void GraphicEngine::Update()
{
    glfwPollEvents();
}

void GraphicEngine::Render()
{
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color[0] * clear_color[3], clear_color[1] * clear_color[3], clear_color[2] * clear_color[3], clear_color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicEngine::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void GraphicEngine::Shutdown()
{
    if (window) {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}
