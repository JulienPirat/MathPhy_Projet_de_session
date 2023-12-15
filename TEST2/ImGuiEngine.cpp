#include "ImGuiEngine.h"

// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "world.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

bool ImGuiEngine::Init(GLFWwindow* _window)
{
	window = _window;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(nullptr);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    return true;
}

void ImGuiEngine::Update()
{
    processInput(window);

    if (visible == false) {
        return;
    }



    auto io = ImGui::GetIO();

    // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Math Phys Tests !");                          // Create a window called "Hello, world!" and append into it.
        ImGui::SetWindowSize(ImVec2(300, 600), 0);

        ImGui::Text("Part 1 :");
        if (ImGui::Button("Demo KDTree")) {
            World& w = World::GetInstance();
            w.AddDemoKDTree();
        }

        
        ImGui::Text("Part 1 :");
        if (ImGui::Button("Spawn Particle")) {
            World& w = World::GetInstance();
            w.GenBasicParticule(0,0,0,0,0,0,0, 0,0);
        }

        if (ImGui::Button("Delete All Particle")) {
            World& w = World::GetInstance();
            w.DeleteAllParticle();
        }

        if (ImGui::Button("Gravity to Particle")) {
            World& w = World::GetInstance();
            w.PutGravityForceGenerator();
        }

        if (ImGui::Button("Drag to Particle")) {
            World& w = World::GetInstance();
            w.PutDragForceGenerator();
        }

        if (ImGui::Button("Origin Anchored Spring to Particle")) {
            World& w = World::GetInstance();
            w.PutAnchoredSpringForceGenerator();
        }

        if (ImGui::Button("Buoyancy to Particle")) {
            World& w = World::GetInstance();
            w.PutBuoyancyForceGenerator();
        }

        if (ImGui::Button("Cable Test")) {
            World& w = World::GetInstance();
            w.AddCableExample();
        }

        if (ImGui::Button("Rod Test")) {
            World& w = World::GetInstance();
            w.AddRodExample();
        }

        ImGui::Text("Part 2 :");
        if (ImGui::Button("Generate Particle Collision")) {
            World& w = World::GetInstance();
            w.GenBasicCollision();
        }

        if (ImGui::Button("Generate Wall Collision")) {
            World& w = World::GetInstance();
            w.GenWallCollision();
        }

        if (ImGui::Button("Generate Contact Resting")) {
            World& w = World::GetInstance();
            w.GenContactResting();
        }

        if (ImGui::Button("Exemple 2 RigidBody With Spring")) {
            World& w = World::GetInstance();
            w.AddAnchoredSpringForTwoRigidBody();
        }

        if (ImGui::Button("Exemple RigidBody With AnchoredSpring")) {
            World& w = World::GetInstance();
            w.AddAnchoredSpringForRigidBody();
        }

        if (ImGui::Button("Add Gravity for all RigidBody")) {
            World& w = World::GetInstance();
            w.AddRigidBody();
        }
        
        if (ImGui::Button("Delete All RigidBody")) {
            World& w = World::GetInstance();
            w.DeleteAllRigidBody();
        }

        ImGui::Checkbox("Show collision window", &show_collision_window);

        ImGui::End();
    }

    if (show_collision_window)
    {
        ImGui::Begin("Collision Window", &show_collision_window);

        if (ImGui::Button("Contact 2 Box RigidBody")) {
            World& w = World::GetInstance();
            w.ContactBoxBox();
        }

        if (ImGui::Button("GenerateContactBoxBox")) {
            World& w = World::GetInstance();
            w.GenerateContactBoxBox();
        }

        if (ImGui::Button("Contact Sphere and Box RigidBody")) {
            World& w = World::GetInstance();
            w.ContactSphereBox();
        }

        if (ImGui::Button("GenerateContactBoxSphere")) {
			World& w = World::GetInstance();
			w.GenerateContactBoxSphere();
		}

        if (ImGui::Button("Contact Sphere and sphere RigidBody")) {
            World& w = World::GetInstance();
            w.ContactSphereSphere();
        }

        if (ImGui::Button("GenerateContactSphereSphere")) {
            World& w = World::GetInstance();
            w.GenerateContactSphereSphere();
        }

        ImGui::End();
    }

    // Rendering
    ImGui::Render();
}

void ImGuiEngine::Render()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiEngine::Shutdown()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiEngine::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    int nextState = glfwGetKey(window, GLFW_KEY_I);
    if (lastState_Key_I != nextState && nextState == GLFW_PRESS) {
        SetVisible(!visible);
    }
    lastState_Key_I = nextState;
}

void ImGuiEngine::SetVisible(bool _visible)
{
    if (visible == _visible) {
        return;
    }

    if (visible) {
        ImGui_ImplGlfw_InstallCallbacks(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    }
    else {
        ImGui_ImplGlfw_RestoreCallbacks(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}
