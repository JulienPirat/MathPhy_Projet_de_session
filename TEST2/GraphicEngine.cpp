#include "GraphicEngine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "learnopengl/shader_m.h"
#include "learnopengl/camera.h"

#include <iostream>


float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

const float minPointScale = 0.1;
const float maxPointScale = 0.7;
const float maxDistance = 100.0;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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
    GLFWwindow* _window = glfwCreateWindow(1280, 720, "BME - Best Moteur Ever", nullptr, nullptr);
    window = _window;

    if (window == nullptr)
        return window;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Disable vsync
    

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
    glEnable(GL_BLEND);
    glEnable(GL_DITHER);
    
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_1D);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_3D);
    
    glShadeModel(GL_SMOOTH);

    // build and compile our shader zprogram
    // ------------------------------------
    ourShader = new Shader("LearnOpenGL/7.4.camera.vs", "LearnOpenGL/7.4.camera.fs");

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

void GraphicEngine::Render(std::vector<Particle*> const &particles, std::vector<RigidBody*> const& bodies)
{
    // render loop
    // -----------
        // per-frame time logic
        // --------------------
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); ///////////////Le Fond de la  fenetre
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // activate shader
    ourShader->use();

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader->setMat4("projection", projection);

    // camera/view transformation
    glm::mat4 view = camera.GetViewMatrix();
    ourShader->setMat4("view", view);
     
    //Set model ?
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    ourShader->setMat4("model", model);

    RenderCube(Vector3D(-10, -2, -10), Vector3D(10, -1, 10), nullptr);

    //draw particles as point of radius 50
    for (auto p : bodies)
    {   
        ourShader->setVec3("objectColor", p->color.x, p->color.y, p->color.z);
        
        float x = p->position.x;
        float y = p->position.y;
        float z = p->position.z;

        RenderCube(Vector3D(x - .25f, y - .25f, z - .25f), Vector3D(x + .25f, y + .25f, z +.25f), p);
	}

    for (auto b : particles)
    {
        ourShader->setVec3("objectColor", b->getColor().x, b->getColor().y, b->getColor().z);
		RenderSphere(b->getPosition());
    }
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

    delete ourShader;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

/*
* Render a cube
* @param topPosition the position of the top of the cube from the back face, facing towards positive x
* @param bottomPosition the position of the bottom of the cube from the front face, facing towards positive x
*/
void GraphicEngine::RenderCube(Vector3D bottomPosition, Vector3D topPosition, RigidBody* b)
{
    //render a cube at the origin using buffers and shaders
    
    //left face
    if(b) ourShader->setVec3("objectColor", b->color.x + .1f, b->color.y - .1f, b->color.z - .1f);
    else ourShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    glBegin(GL_QUADS);
    glVertex3f(bottomPosition.x , bottomPosition.y, bottomPosition.z); //bottom left
    glVertex3f(bottomPosition.x, topPosition.y, bottomPosition.z); //bottom right
    glVertex3f(bottomPosition.x, topPosition.y, topPosition.z); //top right
    glVertex3f(bottomPosition.x, bottomPosition.y, topPosition.z); //top left
    glEnd();

    //right face
    if (b) ourShader->setVec3("objectColor", b->color.x - .1f, b->color.y - .1f, b->color.z + .1f);
    else ourShader->setVec3("objectColor", .4f, .2f, 0.31f);
    glBegin(GL_QUADS);
    glVertex3f(topPosition.x, bottomPosition.y , bottomPosition.z); //bottom left
    glVertex3f(topPosition.x, topPosition.y, bottomPosition.z); //bottom right
    glVertex3f(topPosition.x, topPosition.y, topPosition.z); //top right
    glVertex3f(topPosition.x, bottomPosition.y, topPosition.z); //top left
    glEnd();

    //bottom face
    if (b) ourShader->setVec3("objectColor", b->color.x - .1f, b->color.y -.1f, b->color.z - .1f);
    else ourShader->setVec3("objectColor", .6f, .7f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(topPosition.x, bottomPosition.y, bottomPosition.z); //bottom left
    glVertex3f(bottomPosition.x, bottomPosition.y , bottomPosition.z); //bottom right
    glVertex3f(bottomPosition.x, bottomPosition.y, topPosition.z); //top right
    glVertex3f(topPosition.x, bottomPosition.y, topPosition.z); //top left
    glEnd();

    //top face
    if (b) ourShader->setVec3("objectColor", b->color.x +.2f, b->color.y + .1f, b->color.z + .1f);
    else ourShader->setVec3("objectColor", .3f, 0.2f, 0.7f);
    glBegin(GL_QUADS);
    glVertex3f(bottomPosition.x, topPosition.y, bottomPosition.z); //bottom left
    glVertex3f(topPosition.x, topPosition.y, bottomPosition.z); //bottom right
    glVertex3f(topPosition.x, topPosition.y, topPosition.z); //top right
    glVertex3f(bottomPosition.x, topPosition.y, topPosition.z); //top left
    glEnd();

    //front face
    if (b) ourShader->setVec3("objectColor", b->color.x + .1f, b->color.y + .1f, b->color.z - .1f);
    else ourShader->setVec3("objectColor", .8f, 0.4f, 0.6f);
    glBegin(GL_QUADS);
    glVertex3f(bottomPosition.x, bottomPosition.y, topPosition.z); //bottom left
    glVertex3f(bottomPosition.x, topPosition.y, topPosition.z); //bottom right
    glVertex3f(topPosition.x, topPosition.y, topPosition.z); //top right
    glVertex3f(topPosition.x, bottomPosition.y, topPosition.z); //top left
    glEnd();

    //back face
    if (b) ourShader->setVec3("objectColor", b->color.x + .1f, b->color.y - .1f, b->color.z + .1f);
    else ourShader->setVec3("objectColor", 1.0f, 1.0f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(topPosition.x, bottomPosition.y, bottomPosition.z); //bottom left
    glVertex3f(topPosition.x, topPosition.y, bottomPosition.z); //bottom right
    glVertex3f(bottomPosition.x, topPosition.y, bottomPosition.z); //top right
    glVertex3f(bottomPosition.x, bottomPosition.y, bottomPosition.z); //top left
    glEnd();
}

void GraphicEngine::RenderSphere(Vector3D position)
{
    float radius = .1f;
    int slices = 10;
    int stacks = 10;
    double pi = 3.141;
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            float phi1 = i * 2 * pi / slices;
            float phi2 = (i + 1) * 2 * pi / slices;
            float theta1 = j * pi / stacks;
            float theta2 = (j + 1) * pi / stacks;

            // Vertices
            float x1 = position.x +radius * sin(theta1) * cos(phi1);
            float y1 = position.y + radius * sin(theta1) * sin(phi1);
            float z1 = position.z + radius * cos(theta1);

            float x2 = position.x + radius * sin(theta1) * cos(phi2);
            float y2 = position.y + radius * sin(theta1) * sin(phi2);
            float z2 = position.z + radius * cos(theta1);

            float x3 = position.x + radius * sin(theta2) * cos(phi1);
            float y3 = position.y + radius * sin(theta2) * sin(phi1);
            float z3 = position.z + radius * cos(theta2);

            float x4 = position.x + radius * sin(theta2) * cos(phi2);
            float y4 = position.y + radius * sin(theta2) * sin(phi2);
            float z4 = position.z + radius * cos(theta2);

            // Draw triangles
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);

            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);
            glVertex3f(x4, y4, z4);
        }
    }

    glEnd();
}

