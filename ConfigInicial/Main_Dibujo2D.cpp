#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h> // Gestion de las extensiones de OpenGL
#include <GLFW/glfw3.h> // Gestion de las entredas 

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600; // Tamaño de la ventana


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);

	//Verificaci�n de errores de creacion  ventana
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

/*  Antes de definir los vertices, hacemos la representacion de cada pixel mediante un vertice c/u
	b  b  n  n  b  n  n  b  b
	b  n r1 r1  n r1 r1  n  b
	n r1  b r1 r1 r1 r1 r1  n
	n r1 r1 r1 r1 r1 r1 r1  n
	n r2 r1 r1 r1 r1 r1 r2  n
	b  n r2 r1 r1 r1 r2  n  b
	b  b  n r2 r1 r2  n  b  b
	b  b  b  n r2  n  b  b  b
	b  b  b  b  n  b  b  b  b

	Donde: 
	b es blanco
	n es negro
	r1 es rojo claro
	r2 es rojo fuerte
*/

	float vertices[] = {
		//Corazon 1 (enmedio)
		0.0f,		0.0f,		0.0f,   0.0f,0.0f,0.0f,  // Contorno (color negro)
		0.052f,		0.097f,		0.0f,   0.0f,0.0f,0.0f,
		0.1035f,	0.194f,		0.0f,	0.0f,0.0f,0.0f,
		0.155f,		0.291f,		0.0f,   0.0f,0.0f,0.0f,
		0.206f,		0.388f,		0.0f,	0.0f,0.0f,0.0f,
		0.206f,		0.485f,		0.0f,	0.0f,0.0f,0.0f,
		0.206f,		0.582f,		0.0f,   0.0f,0.0f,0.0f,
		0.155f,		0.679f,		0.0f,   0.0f,0.0f,0.0f,
		0.1035f,    0.776f,		0.0f,   0.0f,0.0f,0.0f,
		0.052f,		0.776f,		0.0f,   0.0f,0.0f,0.0f,
		0.0f,		0.679f,		0.0f,   0.0f,0.0f,0.0f,
		-0.051f,	0.776f,		0.0f,   0.0f,0.0f,0.0f,
		-0.102f,	0.776f,		0.0f,	0.0f,0.0f,0.0f,
		-0.153f,	0.679f,		0.0f,   0.0f,0.0f,0.0f,
		-0.204f,	0.582f,		0.0f,   0.0f,0.0f,0.0f,
		-0.204f,	0.485f,		0.0f,   0.0f,0.0f,0.0f,
		-0.204f,	0.388f,		0.0f,   0.0f,0.0f,0.0f,
		-0.153f,	0.291f,		0.0f,   0.0f,0.0f,0.0f,
		-0.102f,	0.194f,		0.0f,   0.0f,0.0f,0.0f,
		-0.051f,	0.097f,		0.0f,   0.0f,0.0f,0.0f,

		0.0f,		0.097f,		0.0f,   0.56078431f,0.0f,0.0f, // relleno color rojo fuerte
		0.052f,		0.194f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		0.1035f,	0.291f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		0.155f,		0.388f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		-0.051f,	0.194f,		0.0f,   0.56078431f,0.0f,0.0f,
		-0.102f,	0.291f,		0.0f,   0.56078431f,0.0f,0.0f,
		-0.153f,	0.388f,		0.0f,   0.56078431f,0.0f,0.0f,

		0.0f,		0.194f,		0.0f,   1.0f,0.00392157f,0.0745098f, //relleno rojo claro
		0.0f,		0.291f,		0.0f,   1.0f,0.00392157f,0.0745098f, //columna 1
		0.0f,		0.388f,		0.0f,   1.0f,0.00392157f,0.0745098f,
		0.0f,		0.485f,		0.0f,   1.0f,0.00392157f,0.0745098f,
		0.0f,		0.582f,		0.0f,   1.0f,0.00392157f,0.0745098f,

		0.052f,		0.291f,		0.0f,   0.1098f, 0.1098f, 0.1098f, //columna 2
		0.052f,		0.388f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		0.052f,		0.485f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		0.052f,		0.582f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		0.052f,		0.679f,		0.0f,   0.1098f, 0.1098f, 0.1098f,

		0.1035f,	0.388f,		0.0f,   0.1098f, 0.1098f, 0.1098f, //columna 3
		0.1035f,	0.485f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		0.1035f,	0.582f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		0.1035f,	0.679f,		0.0f,   0.1098f, 0.1098f, 0.1098f,

		0.155f,		0.485f,		0.0f,  0.1098f, 0.1098f, 0.1098f, //columna 4
		0.155f,		0.582f,		0.0f,   0.1098f, 0.1098f, 0.1098f,

		-0.051f,	0.291f,		0.0f,   1.0f,0.00392157f,0.0745098f, //columna 5
		-0.051f,	0.388f,		0.0f,   1.0f,0.00392157f,0.0745098f,
		-0.051f,	0.485f,		0.0f,   1.0f,0.00392157f,0.0745098f,
		-0.051f,	0.582f,		0.0f,   1.0f,0.00392157f,0.0745098f,
		-0.051f,	0.679f,		0.0f,   1.0f,0.00392157f,0.0745098f,

		-0.102f,	0.388f,		0.0f,   1.0f,0.00392157f,0.0745098f, //columna 6
		-0.102f,	0.485f,		0.0f,   1.0f,0.00392157f,0.0745098f,
		-0.102f,	0.582f,		0.0f,   1.0f,1.0f,1.0f, //este vertice aparenta brillo
		-0.102f,	0.679f,		0.0f,   1.0f,0.00392157f,0.0745098f,

		-0.153f,	0.485f,		0.0f,   1.0f,0.00392157f,0.0745098f, //columna 7
		-0.153f,	0.582f,		0.0f,   1.0f,0.00392157f,0.0745098f,

		// corazon 2 (derecha)
		.5 + 0.0f,		0.0f,		0.0f,   0.0f, 0.0f, 0.0f,  // Contorno
		.5 + 0.05f,		0.097f,		0.0f,   0.0f, 0.0f, 0.0f,
		.5 + 0.101f,	0.194f,		0.0f,	0.0f,0.0f,0.0f,
		.5 + 0.153f,	0.291f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + 0.204f,	0.388f,		0.0f,	0.0f,0.0f,0.0f,
		.5 + 0.204f,	0.485f,		0.0f,	0.0f,0.0f,0.0f,
		.5 + 0.204f,	0.582f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + 0.153f,	0.679f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + 0.1035f,   0.776f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + 0.052f,	0.776f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + 0.0f,		0.679f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + -0.051f,	0.776f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + -0.102f,	0.776f,		0.0f,	0.0f,0.0f,0.0f,
		.5 + -0.153f,	0.679f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + -0.204f,	0.582f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + -0.204f,	0.485f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + -0.204f,	0.388f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + -0.153f,	0.291f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + -0.102f,	0.194f,		0.0f,   0.0f,0.0f,0.0f,
		.5 + -0.051f,	0.097f,		0.0f,   0.0f,0.0f,0.0f,

		.5 + 0.0f,		0.097f,		0.0f,   0.1098f, 0.1098f, 0.1098f, // relleno color rojo fuerte
		.5 + 0.05f,		0.194f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		.5 + 0.1031f,	0.291f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		.5 + 0.153f,	0.388f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		.5 + -0.051f,	0.194f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		.5 + -0.102f,	0.291f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		.5 + -0.153f,	0.388f,		0.0f,   0.1098f, 0.1098f, 0.1098f,

		.5 + 0.0f,		0.194f,		0.0f,   0.1098f, 0.1098f, 0.1098f, //relleno rojo claro
		0.5f,			0.291f,		0.0f,   0.1098f, 0.1098f, 0.1098f, //columna 1
		0.5f,			0.388f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		0.5f,			0.485f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		0.5f,			0.582f,		0.0f,   0.1098f, 0.1098f, 0.1098f,

		.5 + 0.051f,	0.291f,		0.0f,   0.1098f, 0.1098f, 0.1098f, //columna 2
		.5 + 0.051f,	0.388f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		.5 + 0.051f,	0.485f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		.5 + 0.051f,	0.582f,		0.0f,   0.1098f, 0.1098f, 0.1098f,
		.5 + 0.051f,	0.679f,		0.0f,   0.1098f, 0.1098f, 0.1098f,

		.5 + 0.1032f,	0.388f,		0.0f, 0.1098f, 0.1098f, 0.1098f, //columna 3
		.5 + 0.1032f,	0.485f,		0.0f, 0.1098f, 0.1098f, 0.1098f,
		.5 + 0.1032f,	0.582f,		0.0f, 0.1098f, 0.1098f, 0.1098f,
		.5 + 0.1032f,	0.679f,		0.0f, 0.1098f, 0.1098f, 0.1098f,

		.5 + 0.152f,	0.485f,		0.0f, 0.1098f, 0.1098f, 0.1098f, //columna 4
		.5 + 0.152f,	0.582f,		0.0f,   0.1098f, 0.1098f, 0.1098f,

		.5 + -0.051f,	0.291f,		0.0f, 0.1098f, 0.1098f, 0.1098f, //columna 5
		.5 + -0.051f,	0.388f,		0.0f, 0.1098f, 0.1098f, 0.1098f,
		.5 + -0.051f,	0.485f,		0.0f, 0.1098f, 0.1098f, 0.1098f,
		.5 + -0.051f,	0.582f,		0.0f, 0.1098f, 0.1098f, 0.1098f,
		.5 + -0.051f,	0.679f,		0.0f, 0.1098f, 0.1098f, 0.1098f,

		.5 + -0.102f,	0.388f,		0.0f, 0.1098f, 0.1098f, 0.1098f, //columna 6
		.5 + -0.102f,	0.485f,		0.0f, 0.1098f, 0.1098f, 0.1098f,
		.5 + -.102f,	0.582f,		0.0f, 0.1098f, 0.1098f, 0.1098f, // "brillo"
		.5 + -0.102f,	0.679f,		0.0f, 0.1098f, 0.1098f, 0.1098f,

		-0.153 + .5f,		0.485f,		0.0f, 0.1098f, 0.1098f, 0.1098f, //columna 7
		-0.153 + .5f,		0.582f,		0.0f, 0.1098f, 0.1098f, 0.1098f,

		// corazon 3 (izquierda)
		-.5 + 0.0f,		0.0f,		0.0f,		0.0f, 0.0f, 0.0f,  // Contorno
		-.5 + 0.05f,	0.097f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + 0.101f,	0.194f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + 0.153f,	0.291f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + 0.204f,	0.388f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + 0.204f,	0.485f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + 0.204f,	0.582f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + 0.153f,	0.679f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + 0.1035f,	0.776f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + 0.052f,	0.776f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + 0.0f,		0.679f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + -0.051f,	0.776f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + -0.102f,	0.776f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + -0.153f,	0.679f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + -0.204f,	0.582f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + -0.204f,	0.485f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + -0.204f,	0.388f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + -0.153f,	0.291f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + -0.102f,	0.194f,		0.0f,		0.0f, 0.0f, 0.0f,
		-.5 + -0.051f,	0.097f,		0.0f,		0.0f, 0.0f, 0.0f,

		-.5 + 0.0f,		0.097f,		0.0f,		0.56078431f, 0.0f, 0.0f, // relleno rojo fuerte
		-.5 + 0.05f,	0.194f,		0.0f,		0.56078431f, 0.0f, 0.0f,
		-.5 + 0.1031f,	0.291f,		0.0f,		0.56078431f, 0.0f, 0.0f,
		-.5 + 0.153f,	0.388f,		0.0f,		0.56078431f, 0.0f, 0.0f,
		-.5 + -0.051f,	0.194f,		0.0f,		0.56078431f, 0.0f, 0.0f,
		-.5 + -0.102f,	0.291f,		0.0f,		0.56078431f, 0.0f, 0.0f,
		-.5 + -0.153f,	0.388f,		0.0f,		0.56078431f, 0.0f, 0.0f,

		-.5 + 0.0f,		0.194f,		0.0f,		1.0f, 0.00392157f, 0.0745098f, //relleno rojo claro
		-0.5f,			0.291f,		0.0f,		1.0f, 0.00392157f, 0.0745098f, //columna 1
		-0.5f,			0.388f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-0.5f,			0.485f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-0.5f,			0.582f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,

		-.5 + 0.051f,	0.291f,		0.0f,		1.0f, 0.00392157f, 0.0745098f, //columna 2
		-.5 + 0.051f,	0.388f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-.5 + 0.051f,	0.485f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-.5 + 0.051f,	0.582f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-.5 + 0.051f,	0.679f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,

		-.5 + 0.1032f,	0.388f,		0.0f,		1.0f, 0.00392157f, 0.0745098f, //columna 3
		-.5 + 0.1032f,	0.485f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-.5 + 0.1032f,	0.582f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-.5 + 0.1032f,	0.679f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,

		-.5 + 0.152f,	0.485f,		0.0f,		1.0f, 0.00392157f, 0.0745098f, //columna 4
		-.5 + 0.152f,	0.582f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,

		-.5 + -0.051f,	0.291f,		0.0f,		1.0f, 0.00392157f, 0.0745098f, //columna 5
		-.5 + -0.051f,	0.388f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-.5 + -0.051f,	0.485f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-.5 + -0.051f,	0.582f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-.5 + -0.051f,	0.679f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,

		-.5 + -0.102f,	0.388f,		0.0f,		1.0f, 0.00392157f, 0.0745098f, //columna 6
		-.5 + -0.102f,	0.485f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
		-.5 + -.102f,	0.582f,		0.0f,		1.0f, 1.0f, 1.0f, // "brillo"
		-.5 + -0.102f,	0.679f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,

		-0.153 - .5f,	0.485f,		0.0f,		1.0f, 0.00392157f, 0.0745098f, //columna 7
		-0.153 - .5f,	0.582f,		0.0f,		1.0f, 0.00392157f, 0.0745098f,
	};

	unsigned int indices[] = {  // note that we start from 0! no use indices :(
		3,2,1,// second Triangle
		0,1,3,


	};



	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)



	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.3961f, 0.6745f, 0.2039f, 1.0f); // ahora cambiamos el fondo a color verde
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);


		glPointSize(35);
		glDrawArrays(GL_POINTS, 0, 300);

		//lDrawArrays(GL_LINES,0,4);
		 //DrawArrays(GL_LINE_LOOP,0,4);

		//lDrawArrays(GL_TRIANGLES,1,3);
	   //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);



		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}