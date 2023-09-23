#include "TEST2/GraphicEngine.h"
#include "TEST2/ImGuiEngine.h"

// Main code
int main(int, char**)
{
    GraphicEngine graphicEngine;
    GLFWwindow* window = graphicEngine.Init();

    if (window == nullptr)
        return 1;

    ImGuiEngine imGuiEngine;
    imGuiEngine.Init(window);

    while (!graphicEngine.ShouldClose())
    {
        graphicEngine.Update();

        imGuiEngine.Update();

        graphicEngine.Render();

        imGuiEngine.Render();

        graphicEngine.SwapBuffers();
    }

    imGuiEngine.Shutdown();

    graphicEngine.Shutdown();

    return 0;
}
