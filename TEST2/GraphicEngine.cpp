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

const float minPointScale = 0.1f;
const float maxPointScale = 0.7f;
const float maxDistance = 100.0f;

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

    // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

    // render boxes
    glBindVertexArray(VAO);
    int i = 0;
    for (auto p : bodies)
    {
        if (p->shape == cuboide) {
            ///DrawCuboide
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            //Translate
            model = glm::translate(model, glm::vec3(p->position.x, p->position.y, p->position.z));
            //Rotate
            model = glm::rotate(model, glm::radians((float)p->rotation.x), glm::vec3(1.0f, 0, 0));
            model = glm::rotate(model, glm::radians((float)p->rotation.z), glm::vec3(0, 1.0f, 0));
            model = glm::rotate(model, glm::radians((float)p->rotation.y), glm::vec3(0, 0, 1.0f));
            //Scale
            model = glm::scale(model, glm::vec3(p->dimension.x, p->dimension.y, p->dimension.z));
            //Color
            ourShader->setVec3("objectColor", p->color.r, p->color.g, p->color.b);
            //Send matrix
            ourShader->setMat4("model", model);
            //Draw
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        else if (p->shape == sphere) {
            ///DrawSphere
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::scale(model, glm::vec3(1, 1, 1));
            ourShader->setVec3("objectColor", p->color.r, p->color.g, p->color.b);
            RenderSphere(p->position, p->dimension.x);
        }
    }

    for (auto b : particles)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1, 1, 1));
        ourShader->setVec3("objectColor", b->getColor().r, b->getColor().g, b->getColor().b);
        RenderSphere(b->getPosition());
    }

    for (auto p : bodies)
    {
        if (p->shape == plane) {
            ///DrawPlane
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            //Translate
            model = glm::translate(model, glm::vec3(p->position.x, p->position.y, p->position.z));
            //Rotate
            model = glm::rotate(model, glm::radians((float)p->rotation.x), glm::vec3(1.0f, 0, 0));
            model = glm::rotate(model, glm::radians((float)p->rotation.z), glm::vec3(0, 1.0f, 0));
            model = glm::rotate(model, glm::radians((float)p->rotation.y), glm::vec3(0, 0, 1.0f));
            //Scale
            model = glm::scale(model, glm::vec3(p->dimension.x, 0.01f, p->dimension.y));
            //Color
            ourShader->setVec3("objectColor", p->color.r, p->color.g, p->color.b);
            //Send matrix
            ourShader->setMat4("model", model);
            //Draw
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
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
    if(b) ourShader->setVec3("objectColor", b->color.r + .1f, b->color.g - .1f, b->color.b - .1f);
    else ourShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    glBegin(GL_QUADS);
    glVertex3f(bottomPosition.x , bottomPosition.y, bottomPosition.z); //bottom left
    glVertex3f(bottomPosition.x, topPosition.y, bottomPosition.z); //bottom right
    glVertex3f(bottomPosition.x, topPosition.y, topPosition.z); //top right
    glVertex3f(bottomPosition.x, bottomPosition.y, topPosition.z); //top left
    glEnd();

    //right face
    if (b) ourShader->setVec3("objectColor", b->color.r - .1f, b->color.g - .1f, b->color.b + .1f);
    else ourShader->setVec3("objectColor", .4f, .2f, 0.31f);
    glBegin(GL_QUADS);
    glVertex3f(topPosition.x, bottomPosition.y , bottomPosition.z); //bottom left
    glVertex3f(topPosition.x, topPosition.y, bottomPosition.z); //bottom right
    glVertex3f(topPosition.x, topPosition.y, topPosition.z); //top right
    glVertex3f(topPosition.x, bottomPosition.y, topPosition.z); //top left
    glEnd();

    //bottom face
    if (b) ourShader->setVec3("objectColor", b->color.r - .1f, b->color.g -.1f, b->color.b - .1f);
    else ourShader->setVec3("objectColor", .6f, .7f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(topPosition.x, bottomPosition.y, bottomPosition.z); //bottom left
    glVertex3f(bottomPosition.x, bottomPosition.y , bottomPosition.z); //bottom right
    glVertex3f(bottomPosition.x, bottomPosition.y, topPosition.z); //top right
    glVertex3f(topPosition.x, bottomPosition.y, topPosition.z); //top left
    glEnd();

    //top face
    if (b) ourShader->setVec3("objectColor", b->color.r +.2f, b->color.g + .1f, b->color.b + .1f);
    else ourShader->setVec3("objectColor", .3f, 0.2f, 0.7f);
    glBegin(GL_QUADS);
    glVertex3f(bottomPosition.x, topPosition.y, bottomPosition.z); //bottom left
    glVertex3f(topPosition.x, topPosition.y, bottomPosition.z); //bottom right
    glVertex3f(topPosition.x, topPosition.y, topPosition.z); //top right
    glVertex3f(bottomPosition.x, topPosition.y, topPosition.z); //top left
    glEnd();

    //front face
    if (b) ourShader->setVec3("objectColor", b->color.r + .1f, b->color.g + .1f, b->color.b - .1f);
    else ourShader->setVec3("objectColor", .8f, 0.4f, 0.6f);
    glBegin(GL_QUADS);
    glVertex3f(bottomPosition.x, bottomPosition.y, topPosition.z); //bottom left
    glVertex3f(bottomPosition.x, topPosition.y, topPosition.z); //bottom right
    glVertex3f(topPosition.x, topPosition.y, topPosition.z); //top right
    glVertex3f(topPosition.x, bottomPosition.y, topPosition.z); //top left
    glEnd();

    //back face
    if (b) ourShader->setVec3("objectColor", b->color.r + .1f, b->color.g - .1f, b->color.b + .1f);
    else ourShader->setVec3("objectColor", 1.0f, 1.0f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(topPosition.x, bottomPosition.y, bottomPosition.z); //bottom left
    glVertex3f(topPosition.x, topPosition.y, bottomPosition.z); //bottom right
    glVertex3f(bottomPosition.x, topPosition.y, bottomPosition.z); //top right
    glVertex3f(bottomPosition.x, bottomPosition.y, bottomPosition.z); //top left
    glEnd();
}

void GraphicEngine::RenderSphere(Vector3D position, double rad)
{
    double radius = rad;
    int slices = 10;
    int stacks = 10;
    double pi = 3.141;
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            double phi1 = i * 2 * pi / slices;
            double phi2 = (i + 1) * 2 * pi / slices;
            double theta1 = j * pi / stacks;
            double theta2 = (j + 1) * pi / stacks;

            // Vertices
            double x1 = position.x +radius * sin(theta1) * cos(phi1);
            double y1 = position.y + radius * sin(theta1) * sin(phi1);
            double z1 = position.z + radius * cos(theta1);

            double x2 = position.x + radius * sin(theta1) * cos(phi2);
            double y2 = position.y + radius * sin(theta1) * sin(phi2);
            double z2 = position.z + radius * cos(theta1);

            double x3 = position.x + radius * sin(theta2) * cos(phi1);
            double y3 = position.y + radius * sin(theta2) * sin(phi1);
            double z3 = position.z + radius * cos(theta2);

            double x4 = position.x + radius * sin(theta2) * cos(phi2);
            double y4 = position.y + radius * sin(theta2) * sin(phi2);
            double z4 = position.z + radius * cos(theta2);

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

