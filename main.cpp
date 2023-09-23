#include "TEST2/GraphicEngine.h"
#include "TEST2/ImGuiEngine.h"
#include <LearnOpenGL/CameraController.h>

// Main code
int main(int, char**)
{
    GraphicEngine graphicEngine;
    GLFWwindow* window = graphicEngine.Init();

    if (window == nullptr)
        return 1;

    ImGuiEngine imGuiEngine;
    imGuiEngine.Init(window);

    CameraController cameraController;
    cameraController.Init(window);

    imGuiEngine.SetVisible(true);

    while (!graphicEngine.ShouldClose())
    {
        graphicEngine.Update();

        imGuiEngine.Update();

        graphicEngine.Render();

        cameraController.Update();

        imGuiEngine.Render();

        graphicEngine.SwapBuffers();
    }

    cameraController.Shutdown();

    imGuiEngine.Shutdown();

    graphicEngine.Shutdown();

    return 0;
}
