#include "TEST2/GraphicEngine.h"
#include "TEST2/ImGuiEngine.h"
#include <PhysicEngine.h>

// Main code
int main(int, char**)
{
    GraphicEngine graphicEngine;
    GLFWwindow* window = graphicEngine.Init();

    if (window == nullptr)
        return 1;

    ImGuiEngine imGuiEngine;
    imGuiEngine.Init(window);

    PhysicEngine physicEngine;
    physicEngine.Init();

    imGuiEngine.SetVisible(true);

    while (!graphicEngine.ShouldClose())
    {
        physicEngine.Update();

        graphicEngine.Update();

        imGuiEngine.Update();

        graphicEngine.Render(physicEngine.GetParticles());

        imGuiEngine.Render();

        graphicEngine.SwapBuffers();
    }

    imGuiEngine.Shutdown();

    graphicEngine.Shutdown();

    return 0;
}
