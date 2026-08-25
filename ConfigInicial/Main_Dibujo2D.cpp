#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600; // DEFINICION DE TAMAÑO DE LA VENTANA


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);// CREACION DE LA VENTANA CON NOMBRE
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion de ventana
	if (window== NULL) 
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

	//Se carga información de los archivos del shader de vértices
	// y del shader de fragmentos a la variable tipo Shader
    Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// DEFINICION DE VERTICES
	// Set up vertex data (and buffer(s)) and attribute pointers
	// Componente de profundidad es 0 porque es 2D
	// Formato de color en RGB [0-1]
	float vertices[] = {
		-0.8f,  0.85f, 0.0f,    0.0f,1.0f,0.0f,  // 1
		-0.7f, 0.9f, 0.0f,    0.5f,1.0f,0.0f,  // 2
		-0.67f, 0.75f, 0.0f,   1.0f, 0.0f, 0.0f,  // 3
		0.8f,  0.85f, 0.0f,   0.0f,0.0f,1.0f, // 4 
		0.7f,  0.9f, 0.0f,   0.0f,0.0f,1.0f,	// 5
		0.67f,  0.75f, 0.0f,   0.0f,0.0f,1.0f,	// 6

		0.0f, 0.2f, 0.0f,		0.0f,0.5f,0.0f,	// 7
		0.06f, 0.25f, 0.0f,		0.5f,0.5f,0.5f,	// 8
		-0.06f, 0.25f, 0.0f,		0.5f,0.5f,0.5f,	// 9
		0.0f, 0.0f, 0.0f,		0.0f,0.5f,0.0f,	// 10
		0.025f, 0.0f, 0.0f,		0.0f,0.5f,0.0f,	// 11
		-0.025f, 0.0f, 0.0f,		0.0f,0.5f,0.0f,	// 12
		0.0f, -0.15f, 0.0f,		0.0f,0.5f,0.0f,	// 13
		0.07f, -0.15f, 0.0f,	1.0f,1.0f,1.0f,	// 14
		-0.07f, -0.15f, 0.0f,	1.0f,1.0f,1.0f,	// 15
		0.0f, -0.45f, 0.0f,		0.0f,0.5f,0.0f,	// 16
		0.1f, -0.34f, 0.0f,		0.0f,1.0f,1.0f,	// 17
		-0.1f, -0.34f, 0.0f,	0.0f,1.0f,1.0f,	// 18


		-0.7f, 0.0f, 0.0f,    0.5f,1.0f,0.0f,	// 19
		0.7f, 0.0f, 0.0f,    0.5f,1.0f,0.0f,	// 20
		-0.55f, -0.10f, 0.0f,    0.5f,1.0f,0.0f,	// 21
		0.55f, -0.10f, 0.0f,    0.5f,1.0f,0.0f,	// 22
		-0.62f, -0.25f, 0.0f,    0.5f,1.0f,0.0f,	// 23
		0.62f, -0.25f, 0.0f,    0.5f,1.0f,0.0f,	// 24
		-0.3f, -0.95f, 0.0f,		0.5f,1.0f,0.0f,	// 25
		-0.27f, -0.75f, 0.0f,	0.5f,1.0f,0.0f,	// 26
		-0.2f, -0.85f, 0.0f,	0.5f,1.0f,0.0f,	// 27
		0.3f, -0.95f, 0.0f,		0.5f,1.0f,0.0f,	// 28
		0.27f, -0.75f, 0.0f,	0.5f,1.0f,0.0f,	// 29
		0.2f, -0.85f, 0.0f,	0.5f,1.0f,0.0f,	// 30

	};

	// Secuencias de vértices no signados
	unsigned int indices[] = {  // note that we start from 0!
		0,1,3,
		3,2,1,// second Triangle
		0,1,3,
		
	};



	// Se carga información de los vértices a los buffers
	GLuint VBO, VAO,EBO;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	// SECCION DE DIBUJO
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        glPointSize(10); // Para definir el tamaño del vértice
        glDrawArrays(GL_POINTS,0,1); // a partir de qué elemento del arreglo va a dibujar
									   // cuántos elementos contiguos se van a ocupar para comenzar a dibujar
        
		glDrawArrays(GL_POINTS, 1, 1);
		glDrawArrays(GL_POINTS, 2, 1);
		glDrawArrays(GL_POINTS, 3, 1);
		glDrawArrays(GL_POINTS, 4, 1);
		glDrawArrays(GL_POINTS, 5, 1);
		glDrawArrays(GL_POINTS, 6, 1);
		glDrawArrays(GL_POINTS, 7, 1);
		glDrawArrays(GL_POINTS, 8, 1);
		glDrawArrays(GL_POINTS, 9, 1);
		glDrawArrays(GL_POINTS, 10, 1); 
		glDrawArrays(GL_POINTS, 11, 1);
		glDrawArrays(GL_POINTS, 12, 1);
		glDrawArrays(GL_POINTS, 13, 1);
		glDrawArrays(GL_POINTS, 14, 1);
		glDrawArrays(GL_POINTS, 15, 1);
		glDrawArrays(GL_POINTS, 16, 1);
		glDrawArrays(GL_POINTS, 17, 1);
		glDrawArrays(GL_POINTS, 18, 1);
		glDrawArrays(GL_POINTS, 19, 1);
		glDrawArrays(GL_POINTS, 20, 1);
		glDrawArrays(GL_POINTS, 21, 1);
		glDrawArrays(GL_POINTS, 22, 1);
		glDrawArrays(GL_POINTS, 23, 1);
		glDrawArrays(GL_POINTS, 24, 1);
		glDrawArrays(GL_POINTS, 25, 1);
		glDrawArrays(GL_POINTS, 26, 1);
		glDrawArrays(GL_POINTS, 27, 1);
		glDrawArrays(GL_POINTS, 28, 1);
		glDrawArrays(GL_POINTS, 29, 1);


		// Para dibujar una linea (sólo toma en cuenta la unión de dos vértices)
        //glDrawArrays(GL_LINES,0,2); // a partir de qué elemento del arreglo va a dibujar
									  // cuántos vértices contiguos se van a usar para dibujar la linea 
        
		// Para dibujar el cuadrado completo (hace todas las líneas)
		//glDrawArrays(GL_LINE_LOOP,0,4);

		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        
		// Para dibujar triángulos
        //glDrawArrays(GL_TRIANGLES,0,3); // a partir de qué elemento del arreglo va a dibujar
										  // cuántos vértices contiguos se van a usar para dibujar el triángulo
		
		// Dibuja por elementos, no por arreglos
		// Para dibujar elementos sin que sean contiguos
        //glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0); // figura por dibujar
														  // tamaño de la figura
														  // elementos no signados de tipo entero
														  // desde dónde se leen los índices

        
        
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