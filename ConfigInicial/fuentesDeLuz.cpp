#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f); 

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f,0.0f, 0.0f), // Posición 0 será la fogata
    glm::vec3(0.0f,0.0f, 0.0f), // Apagada
    glm::vec3(0.0f,0.0f,  0.0f), // Apagada
    glm::vec3(0.0f,0.0f, 0.0f)  // Apagada
};


float vertices[] = {
    
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


// Deltatime
GLfloat deltaTime = 0.0f;       // Time between current frame and last frame
GLfloat lastFrame = 0.0f;       // Time of last frame

// Velocidad de movimiento de la fogata
GLfloat lightMoveSpeed = 1.5f;

// Posiciones para los modelos de luces
glm::vec3 fogataPos = glm::vec3(-1.1f, 0.8f, -1.0f);
glm::vec3 lunaPos = glm::vec3(1.5f, 2.0f, -1.0f);
glm::vec3 linternaPos = glm::vec3(1.5f, -0.3f, 0.9f);
glm::vec3 alienPos = glm::vec3(-1.5f, -0.2f, 1.5f); // Target de la linterna


int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    /* (Dejo comentadas tus opciones originales por si las necesitas)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    */

    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 9 - Romero Pizano Christian Gustavo", nullptr, nullptr);
    

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
   
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST); // Habilita el Z-buffer


    // Build and compile our shader program
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

    // Carga de modelos
    Model Dog((char*)"Models/esfera/ball.obj");
    Model Piso((char*)"Models/piso/piso.obj");
    Model alien((char*)"Models/alien/toyUFO.obj");
    Model cohete((char*)"Models/cohete/tripo_convert_84b8bfd5-eead-4e8a-a6ab-c9f4eae57cfb.obj");
    Model meteoro((char*)"Models/meteoro/tripo_convert_542cf2d3-fa56-472a-8408-9e70cc4b0083.obj");
    Model satelite((char*)"Models/satelite/tripo_convert_69d018bb-23a1-4f4b-b19b-fd2c46ff5283.obj");
    Model planeta((char*)"Models/planeta/tripo_convert_5d7e7989-6038-49c7-8a54-9b04bf3d3b4d.obj");

    // nuevos modelos (luces)
    Model fogata((char*)"Models/fogata/fogata.obj");
    Model luna((char*)"Models/luna/luna.obj");
    Model linterna((char*)"Models/linterna/linterna.obj");


    // Set texture units
    lightingShader.Use();
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);
    lampShader.Use();
    glUniform1i(glGetUniformLocation(lampShader.Program, "material.diffuse"), 0);

    // Matriz de proyección
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {

        // Calculate deltatime of current frame
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        pointLightPositions[0] = fogataPos;
        lightingShader.Use();

        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);


        glm::vec3 dirLightDirection = glm::normalize(glm::vec3(0.0f) - lunaPos); // Apunta desde la luna al centro
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), dirLightDirection.x, dirLightDirection.y, dirLightDirection.z);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.05f, 0.05f, 0.08f); // Luz ambiental muy sutil
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.3f);  // Luz difusa más baja
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.1f, 0.1f, 0.1f); // Brillo especular bajo

        GLfloat time = glfwGetTime();
        glm::vec3 lightColor;
        lightColor.x = 0.9f + abs(sin(time * 2.1f)) * 0.1f; // Naranja
        lightColor.y = 0.5f + abs(sin(time * 1.8f)) * 0.15f; // Amarillo
        lightColor.z = 0.1f; // Rojo bajo

        glm::vec3 fogataAmbient = lightColor * 0.1f;
        glm::vec3 fogataDiffuse = lightColor * 0.8f;
        glm::vec3 fogataSpecular = glm::vec3(1.0f, 0.5f, 0.2f);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), fogataAmbient.x, fogataAmbient.y, fogataAmbient.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), fogataDiffuse.x, fogataDiffuse.y, fogataDiffuse.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), fogataSpecular.x, fogataSpecular.y, fogataSpecular.z);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);

        for (int i = 1; i < 4; i++)
        {
            std::string base = "pointLights[" + std::to_string(i) + "].";
            glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "position").c_str()), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "ambient").c_str()), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "diffuse").c_str()), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, (base + "specular").c_str()), 0.0f, 0.0f, 0.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, (base + "constant").c_str()), 1.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, (base + "linear").c_str()), 0.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, (base + "quadratic").c_str()), 0.0f);
        }

        glm::vec3 linternaDir = glm::normalize(alienPos - linternaPos);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), linternaPos.x, linternaPos.y, linternaPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), linternaDir.x, linternaDir.y, linternaDir.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.045f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.0075f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

        // Configura matrices View y Projection
        glm::mat4 view = camera.GetViewMatrix();
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);

        // Dibuja el Piso
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Piso.Draw(lightingShader);

        // Dibuja el Alien
        model = glm::mat4(1.0f);
        model = glm::translate(model, alienPos); // Usa la misma pos que el target
        model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        alien.Draw(lightingShader);

        // Dibuja el Satélite
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.5f, 3.0f, -1.0f));
        model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        satelite.Draw(lightingShader);

        // Dibuja el Cohete
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.5f, 0.3f, 0.0f));
        model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
        model = glm::rotate(model, glm::radians(-80.0f), glm::vec3(0.0f, 0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 0.2f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        cohete.Draw(lightingShader);

        // Dibuja el Planeta
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.5f, 1.0f, 1.0f));
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        planeta.Draw(lightingShader);

        // Dibuja el Meteoro
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.5f, 1.3f, -0.5f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        meteoro.Draw(lightingShader);


        lampShader.Use();
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projLoc = glGetUniformLocation(lampShader.Program, "projection");

        // Set matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        model = glm::mat4(1.0f);
        model = glm::translate(model, lunaPos); 
        model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        luna.Draw(lampShader); 

        // Dibuja la Linterna (brilla en blanco)
        model = glm::mat4(1.0f);
        model = glm::translate(model, linternaPos); 
        model = glm::scale(model, glm::vec3(2.4f, 2.4f, 2.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        linterna.Draw(lampShader); 


        lightingShader.Use();
        // (Las matrices V y P ya están seteadas en este shader)
        modelLoc = glGetUniformLocation(lightingShader.Program, "model");

        // Configuración para transparencia
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE); // No escribir en el depth buffer

        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);

        model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Dog.Draw(lightingShader);

   
        model = glm::mat4(1.0f);
        model = glm::translate(model, fogataPos); // Usa la variable que se mueve
        model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        fogata.Draw(lightingShader); 

        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);


        // Swap the screen buffers
        glfwSwapBuffers(window);
    } // Fin del game loop

    // Properly de-allocate all resources
    glfwTerminate();
    return EXIT_SUCCESS;
} 

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}


void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    GLfloat velocity = lightMoveSpeed * deltaTime;


    if (keys[GLFW_KEY_I]) // Mover hacia adelante (eje Z negativo)
        fogataPos.z -= velocity;
    if (keys[GLFW_KEY_K]) // Mover hacia atrás (eje Z positivo)
        fogataPos.z += velocity;
    if (keys[GLFW_KEY_J]) // Mover hacia la izquierda (eje X negativo)
        fogataPos.x -= velocity;
    if (keys[GLFW_KEY_L]) // Mover hacia la derecha (eje X positivo)
        fogataPos.x += velocity;
    if (keys[GLFW_KEY_U]) // Mover hacia arriba (eje Y positivo)
        fogataPos.y += velocity;
    if (keys[GLFW_KEY_O]) // Mover hacia abajo (eje Y negativo)
        fogataPos.y -= velocity;
}