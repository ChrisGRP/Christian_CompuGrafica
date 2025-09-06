#include <iostream>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window); // permite las entradas del teclado

// variables constantes
const GLint WIDTH = 800, HEIGHT = 600; // tamano de la ventana
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;

int main() {
    glfwInit(); // verificacion de compatibilidad

    // Crear la ventana de GLFW
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // hace que no sea redimensionable
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4 - Romero Christian", nullptr, nullptr);

    // creo que ajusta la ventana a la resolucion de la pantalla
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

    glViewport(0, 0, screenWidth, screenHeight); // define las dimensiones del viewport
    glEnable(GL_DEPTH_TEST); // habilitar prueba de profundidad

    glEnable(GL_BLEND); // habilitar soporte de alfa
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // configuración del blend

    Shader ourShader("Shader/core.vs", "Shader/core.frag"); //supongo que trae los shaders

    // creamos los arreglos de vertices (uno por cada color)
    float maceta[] = {
        -0.5f, -0.5f, 0.5f,  0.6196f, 0.30196f,0.145f, //enfrente
         0.5f, -0.5f, 0.5f,  0.6196f, 0.30196f,0.145f,
         0.5f,  0.5f, 0.5f,  0.6196f, 0.30196f,0.145f,
         0.5f,  0.5f, 0.5f,  0.6196f, 0.30196f,0.145f,
        -0.5f,  0.5f, 0.5f,  0.6196f, 0.30196f,0.145f,
        -0.5f, -0.5f, 0.5f,  0.6196f, 0.30196f,0.145f,

        -0.5f, -0.5f,-0.5f, 0.4941f, 0.22352f,0.09411f,//atras
         0.5f, -0.5f,-0.5f, 0.4941f, 0.22352f,0.09411f,
         0.5f,  0.5f,-0.5f, 0.4941f, 0.22352f,0.09411f,
         0.5f,  0.5f,-0.5f, 0.4941f, 0.22352f,0.09411f,
        -0.5f,  0.5f,-0.5f, 0.4941f, 0.22352f,0.09411f,
        -0.5f, -0.5f,-0.5f, 0.4941f, 0.22352f,0.09411f,

         0.5f, -0.5f,  0.5f,  0.6196f, 0.30196f,0.145f, //izquierda
         0.5f, -0.5f, -0.5f,  0.4941f, 0.22352f,0.09411f,
         0.5f,  0.5f, -0.5f,  0.4941f, 0.22352f,0.09411f,
         0.5f,  0.5f, -0.5f,  0.4941f, 0.22352f,0.09411f,
         0.5f,  0.5f,  0.5f,  0.6196f, 0.30196f,0.145f,
         0.5f, -0.5f,  0.5f,  0.6196f, 0.30196f,0.145f,

        -0.5f,  0.5f,  0.5f,  0.6196f, 0.30196f,0.145f, //derecha
        -0.5f,  0.5f, -0.5f,  0.4941f, 0.22352f,0.09411f,
        -0.5f, -0.5f, -0.5f,  0.4941f, 0.22352f,0.09411f,
        -0.5f, -0.5f, -0.5f,  0.4941f, 0.22352f,0.09411f,
        -0.5f, -0.5f,  0.5f,  0.6196f, 0.30196f,0.145f,
        -0.5f,  0.5f,  0.5f,  0.6196f, 0.30196f,0.145f,

        -0.5f, -0.5f, -0.5f,  0.6196f, 0.30196f,0.145f, //arriba
         0.5f, -0.5f, -0.5f,  0.6196f, 0.30196f,0.145f,
         0.5f, -0.5f,  0.5f,  0.6196f, 0.30196f,0.145f,
         0.5f, -0.5f,  0.5f,  0.6196f, 0.30196f,0.145f,
        -0.5f, -0.5f,  0.5f,  0.6196f, 0.30196f,0.145f,
        -0.5f, -0.5f, -0.5f,  0.6196f, 0.30196f,0.145f,

        -0.5f,  0.5f, -0.5f, 0.4941f, 0.22352f,0.09411f, //abajp
         0.5f,  0.5f, -0.5f, 0.4941f, 0.22352f,0.09411f,
         0.5f,  0.5f,  0.5f, 0.4941f, 0.22352f,0.09411f,
         0.5f,  0.5f,  0.5f, 0.4941f, 0.22352f,0.09411f,
        -0.5f,  0.5f,  0.5f, 0.4941f, 0.22352f,0.09411f,
        -0.5f,  0.5f, -0.5f, 0.4941f, 0.22352f,0.09411f,
    };

    float lanzaguisantes[] = {
    -0.5f, -0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f, // enfrente
     0.5f, -0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,
     0.5f,  0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,
     0.5f,  0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,
    -0.5f,  0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,
    -0.5f, -0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,

    -0.5f, -0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f, // atras
     0.5f, -0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
     0.5f,  0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
     0.5f,  0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
    -0.5f,  0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
    -0.5f, -0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,

    -0.5f,  0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f, // izquierda
    -0.5f,  0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
    -0.5f, -0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
    -0.5f, -0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
    -0.5f, -0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,
    -0.5f,  0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,

     0.5f,  0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f, // derecha
     0.5f,  0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
     0.5f, -0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
     0.5f, -0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
     0.5f, -0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,
     0.5f,  0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,

     -0.5f,  0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f, // arriba
      0.5f,  0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,
      0.5f,  0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
      0.5f,  0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
     -0.5f,  0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
     -0.5f,  0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,

     -0.5f, -0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,  // abajo
      0.5f, -0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,
      0.5f, -0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
      0.5f, -0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
     -0.5f, -0.5f, -1.5f, 0.3686f, 0.5725f, 0.0f,
     -0.5f, -0.5f,  1.5f, 0.3686f, 0.5725f, 0.0f,

    };

    float ojos[] = {
-0.5f, -0.5f,  1.5f, 0.0f, 0.0f, 0.0f, // enfrente
 0.5f, -0.5f,  1.5f, 0.0f, 0.0f, 0.0f,
 0.5f,  0.5f,  1.5f, 0.0f, 0.0f, 0.0f,
 0.5f,  0.5f,  1.5f, 0.0f, 0.0f, 0.0f,
-0.5f,  0.5f,  1.5f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f,  1.5f, 0.0f, 0.0f, 0.0f,

-0.5f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f, // atras
 0.5f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
 0.5f,  0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
 0.5f,  0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
-0.5f,  0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f,

-0.5f,  0.5f,  1.5f, 0.0f, 0.0f, 0.0f, // izquierda
-0.5f,  0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f,  1.5f, 0.0f, 0.0f, 0.0f,
-0.5f,  0.5f,  1.5f, 0.0f, 0.0f, 0.0f,

 0.5f,  0.5f,  1.5f, 0.0f, 0.0f, 0.0f, // derecha
 0.5f,  0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
 0.5f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
 0.5f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
 0.5f, -0.5f,  1.5f, 0.0f, 0.0f, 0.0f,
 0.5f,  0.5f,  1.5f, 0.0f, 0.0f, 0.0f,

 -0.5f,  0.5f,  1.5f, 0.0f, 0.0f, 0.0f, // arriba
  0.5f,  0.5f,  1.5f, 0.0f, 0.0f, 0.0f,
  0.5f,  0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
  0.5f,  0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
 -0.5f,  0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
 -0.5f,  0.5f,  1.5f, 0.0f, 0.0f, 0.0f,

 -0.5f, -0.5f,  1.5f, 0.0f, 0.0f, 0.0f,  // abajo
  0.5f, -0.5f,  1.5f, 0.0f, 0.0f, 0.0f,
  0.5f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
  0.5f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
 -0.5f, -0.5f, -1.5f, 0.0f, 0.0f, 0.0f,
 -0.5f, -0.5f,  1.5f, 0.0f, 0.0f, 0.0f,

    };

    // GLuint == unsigned int 
    GLuint VAO_maceta, VBO_maceta;
    GLuint VAO_lanzaguisantes, VBO_lanzaguisantes;
    GLuint VAO_ojos, VBO_ojos;

    // Configuracion maceta
    glGenVertexArrays(1, &VAO_maceta); // crea el VAO
    glGenBuffers(1, &VBO_maceta); // crea el VBO
    glBindVertexArray(VAO_maceta); // lo converte en un arreglo de vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO_maceta); // carga los datos en la gpu
    glBufferData(GL_ARRAY_BUFFER, sizeof(maceta), maceta, GL_STATIC_DRAW); // lo mismo

    // Atributo 0 = posición (x, y, z)
    // Cada vértice tiene 6 floats (3 de posicion y 3 de color).
    // Toma los primeros 3 floats 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atributo 1 = color (r, g, b)
    // Cada vertice tiene 6 floats (3 de posicion y 3 de color).
    // Toma los siguientes 3 floats (offset = 3 * sizeof(float)).
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // Activa el atributo 1 (color).
    glBindVertexArray(0); //lo desactiva para evitar modificarlo por error despues

    // Configuracion lanzaguisantes
    glGenVertexArrays(1, &VAO_lanzaguisantes);
    glGenBuffers(1, &VBO_lanzaguisantes);
    glBindVertexArray(VAO_lanzaguisantes);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_lanzaguisantes);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lanzaguisantes), lanzaguisantes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    // Configuracion ojos
    glGenVertexArrays(1, &VAO_ojos);
    glGenBuffers(1, &VBO_ojos);
    glBindVertexArray(VAO_ojos);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ojos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ojos), ojos, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    // Proyeccion, vista
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        Inputs(window);
        glfwPollEvents();

        glClearColor(0.3f, 0.4f, 0.6f, 1.0f); // ponemos un fondo azul
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activa el shader
        ourShader.Use();

        glm::mat4 model = glm::mat4(1.0f); // matriz que permite transformar los modelos
        glm::mat4 view = glm::mat4(1.0f);  // matriz que transforma la vista

        view = glm::translate(view, glm::vec3(movX, movY, movZ)); // traslacion para la vista
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f)); // rotacion para la vista

        // obtiene las transformaciones de los shaders
        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

        //pasa la informacion al shader
        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // Renderizar la maceta
        glBindVertexArray(VAO_maceta);
        model = glm::mat4(1.0f); // inicializa la matriz del modelo
        model = glm::scale(model, glm::vec3(0.35f, 0.4625f, 0.4f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); //pasa la matriz transformada al shader
        glDrawArrays(GL_TRIANGLES, 0, 36); // dibuja los vertices
        glBindVertexArray(0); // desenlaza el vao

        // Renderizar el lanzaguisantes
        glBindVertexArray(VAO_lanzaguisantes);
        // cuello
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.2f, 1.0f, .06f)); // Escalamos el lanzaguisantes
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));  // Posición
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // cabeza
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.7f, 0.6f, 0.2f));
        model = glm::translate(model, glm::vec3(0.0f, 1.6f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // trompa
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.45f, 0.35f, 0.15f));
        model = glm::translate(model, glm::vec3(0.0f, 2.2f, 2.5f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Renderizar los ojos
        glBindVertexArray(VAO_ojos);
        // izquierdo 
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.22f, 0.22f, 0.025f)); 
        model = glm::translate(model, glm::vec3(0.9f, 4.8f, 12.0f));  
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // derecho
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(.22f, 0.22f, 0.025f)); // Escalamos el lanzaguisantes
        model = glm::translate(model, glm::vec3(-0.9f, 4.8f, 12.0f));  // Posición
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO_maceta);
    glDeleteBuffers(1, &VBO_maceta);
    glDeleteVertexArrays(1, &VAO_lanzaguisantes);
    glDeleteBuffers(1, &VBO_lanzaguisantes);

    glfwTerminate();
    return EXIT_SUCCESS;
}


void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movX += 0.008f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movX -= 0.008f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movY += 0.008f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movY -= 0.008f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        movZ -= 0.008f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        movZ += 0.008f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rot += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rot -= 0.08f;
}