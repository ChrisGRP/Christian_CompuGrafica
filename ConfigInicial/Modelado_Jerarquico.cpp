//Romero Pizano Christian Gustavo
//Practica 5
//319225596
//12 de septiembre del 2025

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 1200, HEIGHT = 800;

// Camara
float
CamX = 0.0f,
CamY = 0.0f,
CamZ = -5.0f,
Rotar = 0.0f,
dedoMedioA = 0.0f, 
dedoMedioB = 0.0f;

// A (Abajo)
// B (Arriba)
float
rotHombro = 0.0f,
rotCodo = 0.0f,
rotMano = 0.0f,
dedoDerechoA = 0.0f,
dedoDerechoB = 0.0f,
dedoIzquierdoA = 0.0f,
dedoIzquierdoB = 0.0f;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 5 - Romero Christian", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");


    float vertices[] = {
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, -0.5f,-0.5f,
        0.5f, -0.5f,-0.5f,
        0.5f,  0.5f,-0.5f,
        0.5f,  0.5f,-0.5f,
        -0.5f,  0.5f,-0.5f,
        -0.5f, -0.5f,-0.5f,

        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  -0.5f, 0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 

    glm::mat4 projection = glm::mat4(1);
    projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

    glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        Inputs(window);
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();
        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);
        glm::mat4 modelTemp = glm::mat4(1.0f); 
        glm::mat4 modelTemp2 = glm::mat4(1.0f); 
        glm::mat4 PosicionMano = glm::mat4(1.0f); 

        view = glm::translate(view, glm::vec3(CamX, CamY, CamZ));
        view = glm::rotate(view, glm::radians(Rotar), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
        GLint uniformColor = ourShader.uniformColor;

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));

        glBindVertexArray(VAO);

        //Hombro
        model = glm::rotate(model, glm::radians(rotHombro), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
        color = glm::vec3(0.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        //Codo
        model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotCodo), glm::vec3(0.0f, 1.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
        color = glm::vec3(2.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Mano
        model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotMano), glm::vec3(1.0f, 0.0f, 0.0f));
        PosicionMano = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //dedoDerechoA
        model = glm::translate(PosicionMano, glm::vec3(0.25f, 0.35f, 0.375f));
        model = glm::rotate(model, glm::radians(dedoDerechoA), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.6f, 0.2f, 0.9f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        //dedoDerechoB
        model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedoDerechoB), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.6f, 0.2f, 0.9f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        model = PosicionMano;

        //dedoIzquierdoA
        model = glm::translate(PosicionMano, glm::vec3(0.25f, 0.35f, -0.375f)); 
        model = glm::rotate(model, glm::radians(dedoIzquierdoA), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(1.0f, 0.2f, 0.3f); 
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        //dedoIzquierdoB
        model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedoIzquierdoB), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(1.0f, 0.2f, 0.3f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 
        
        model = PosicionMano;

        //dedoMedioA
        model = glm::translate(PosicionMano, glm::vec3(0.25f, 0.35f, 0.0f));
        model = glm::rotate(model, glm::radians(dedoMedioA), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.0f, 0.8f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //dedoMedioB
        model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(dedoMedioB), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(0.0f, 0.8f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        //dedoIzqBajoA
        model = glm::translate(PosicionMano, glm::vec3(0.25f, -0.35f, -0.25f)); 
        model = glm::rotate(model, glm::radians(-dedoMedioA), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(1.0f, 0.5f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //dedoIzqBajoB
        model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-dedoMedioB), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(1.0f, 0.5f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        //dedoDerBajoA
        model = glm::translate(PosicionMano, glm::vec3(0.25f, -0.35f, 0.25f)); 
        model = glm::rotate(model, glm::radians(-dedoMedioA), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(1.0f, 0.0f, 1.0f); 
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        //dedoDerBajoB
        model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-dedoMedioB), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        CamX += 0.008f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        CamX -= 0.008f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        CamY += 0.008f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        CamY -= 0.008f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        CamZ -= 0.008f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        CamZ += 0.008f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        Rotar += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        Rotar -= 0.08f;


    //ControlHombro
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        rotHombro += 0.18f;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        rotHombro -= 0.18f;
    }

    //ControlCodo
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        if (rotCodo < 0.0f) {
            rotCodo += 0.18f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        if (rotCodo >= -90.0f) {
            rotCodo -= 0.18f;
        }
    }

    //ControlMano
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        if (rotMano < 45.0f) {
            rotMano += 0.18f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        if (rotMano > -45.0f) {
            rotMano -= 0.18f;
        }
    }

    //ControlDedos
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        if (dedoDerechoA > -4.72f) {
            dedoDerechoA -= 0.18f;
            dedoIzquierdoA -= 0.18f;
            dedoMedioA -= 0.18f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        if (dedoDerechoA < 60.54f) {
            dedoDerechoA += 0.18f;
            dedoIzquierdoA += 0.18f;
            dedoMedioA += 0.18f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        if (dedoDerechoB > -60.72f) {
            dedoDerechoB -= 0.18f;
            dedoIzquierdoB -= 0.18f;
            dedoMedioB -= 0.18f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        if (dedoDerechoB < 0.0f) {
            dedoDerechoB += 0.18f;
            dedoIzquierdoB += 0.18f;
            dedoMedioB += 0.18f;
        }
    }
}