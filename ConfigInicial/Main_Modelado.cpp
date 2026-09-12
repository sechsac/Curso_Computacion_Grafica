/*
Práctica 4. Modelado Geométrico
Hernández Castro Laura Isabel
Fecha: 11/09/2026
No. de cuenta: 320293634
*/


#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f; // Ayudan a manipular la vista sin cerrar el programa
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4. Modelado geometrico - Hernandez Castro Laura Isabel", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,
      
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania


	// Paleta de colores basada en la imagen
	glm::vec3 colorBlanco = glm::vec3(0.95f, 0.95f, 0.98f);
	glm::vec3 colorBlancoP = glm::vec3(0.95f, 0.93f, 0.91f);
	glm::vec3 colorRosaCuerpo = glm::vec3(0.95f, 0.45f, 0.55f);
	glm::vec3 colorAzulCuerpo = glm::vec3(0.40f, 0.85f, 0.95f);
	glm::vec3 colorRosaPastel = glm::vec3(0.98f, 0.70f, 0.85f);
	glm::vec3 colorMorado = glm::vec3(0.60f, 0.20f, 0.80f);
	glm::vec3 colorAzulOjo = glm::vec3(0.10f, 0.30f, 0.85f);
	glm::vec3 colorRojoNostril = glm::vec3(0.90f, 0.15f, 0.20f);
	glm::vec3 colorPurpuraRay = glm::vec3(0.75f, 0.45f, 0.90f);



	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.7f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		view = glm::translate(view, glm::vec3(movX, movY, movZ)); // Se le manda el valor de la variable, ya no el específico
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		// Para añadir los colores de la figura
		GLint colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);


		// UNICORNIO
		// Cabeza
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlancoP));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.85f, 1.3f)); // Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	
		// Orejas
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlancoP));
		// Izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.45f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(1.6f, 2.5f, -2.2f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.4f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(2.6f, 2.5f, -2.2f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.45f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-1.6f, 2.5f, -2.2f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.4f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-2.6f, 2.5f, -2.2f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Tupé
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorMorado));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.95f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 6.4f, -0.2f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorPurpuraRay));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.64f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 7.4f, -0.3f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cuerno
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlanco));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.3f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 8.4f, -0.8f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 9.3f, -1.95f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 10.2f, -1.95f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Cuello
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlancoP));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.2f, 0.65f)); // Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.12f, -0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pelo del cuello
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorMorado));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 1.05f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 0.4f, -4.55f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.8f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 0.4f, -5.5f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.64f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 0.35f, -6.5f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.48f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 0.35f, -7.5f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojos
		// Izquierdo
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorAzulOjo));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(3.6f, 3.6f, -0.4f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(3.6f, 2.6f, -0.4f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlanco));
		model = glm::mat4(1.0f); // blanco
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(3.6f, 3.6f, -1.4f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorAzulOjo));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(3.6f, 2.6f, -1.4f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Derecho
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-3.6f, 3.6f, -0.4f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-3.6f, 2.6f, -0.4f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlanco));
		model = glm::mat4(1.0f); // blanco
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-3.6f, 3.6f, -1.4f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorAzulOjo));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-3.6f, 2.6f, -1.4f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Nariz
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorRojoNostril));
		// Izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.4f, 0.08f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(1.2f, 1.3f, 8.15f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.4f, 0.08f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-1.2f, 1.3f, 8.15f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Cuerpo
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlancoP));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.75f, 1.7f)); // Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(0.0f, -0.6f, -0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Patas
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlancoP));
		// Izquierda delantera
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.35f)); // Tamaño de la pata
		model = glm::translate(model, glm::vec3(0.95f, -2.5f, -0.5f)); // Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pezuña
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorRosaCuerpo));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.35f)); // Tamaño de la pata
		model = glm::translate(model, glm::vec3(0.95f, -12.5f, -0.5f)); // Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Derecha delantera
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlancoP));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.35f)); // Tamaño de la pata
		model = glm::translate(model, glm::vec3(-0.95f, -2.5f, -0.5f)); // Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pezuña
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorRosaCuerpo));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.35f)); // Tamaño de la pata
		model = glm::translate(model, glm::vec3(-0.95f, -12.5f, -0.5f)); // Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Izquierda trasera
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlancoP));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.35f)); // Tamaño de la pata
		model = glm::translate(model, glm::vec3(0.95f, -2.5f, -4.4f)); // Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pezuña
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorRosaCuerpo));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.35f)); // Tamaño de la pata
		model = glm::translate(model, glm::vec3(0.95f, -12.5f, -4.4f)); // Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Derecha trasera
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlancoP));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.35f, 0.4f, 0.35f)); // Tamaño de la pata
		model = glm::translate(model, glm::vec3(-0.95f, -2.5f, -4.4f)); // Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pezuña
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorRosaCuerpo));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.35f)); // Tamaño de la pata
		model = glm::translate(model, glm::vec3(-0.95f, -12.5f, -4.4f)); // Posición de la pata
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pelo de la cola
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorMorado));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.48f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.1f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorPurpuraRay));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.48f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -3.1f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorPurpuraRay));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.48f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -3.66f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorMorado));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.9f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, -0.41f, -11.0f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorPurpuraRay));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.9f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, -0.41f, -12.0f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorMorado));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.45f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, -4.6f, -4.7f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorPurpuraRay));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.45f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(0.0f, -3.6f, -4.7f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Rayito
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorRosaPastel));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.08f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(6.0f, -2.25f, -8.1f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.08f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(6.0f, -3.25f, -9.1f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Alas
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorAzulCuerpo));
		// Izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.65f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(2.6f, 2.6f, -2.0f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.65f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(2.6f, 0.25f, -5.6f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlanco));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.65f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(2.6f, 0.1f, -6.6f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.3f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(2.6f, 0.67f, -7.6f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(2.6f, 1.67f, -8.6f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Derecha
		glUniform3fv(colorLoc, 1, glm::value_ptr(colorAzulCuerpo));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.65f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-2.6f, 2.6f, -2.0f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.65f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-2.6f, 0.25f, -5.6f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3fv(colorLoc, 1, glm::value_ptr(colorBlanco));
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.65f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-2.6f, 0.1f, -6.6f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.3f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-2.6f, 0.67f, -7.6f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f)); // Tamaño del palito
		model = glm::translate(model, glm::vec3(-2.6f, 1.67f, -8.6f)); // Posición del palito
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);




		glBindVertexArray(0);	

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 // CON LA VARIACIÓN DE ESTOS VALORES SE MODIFICA LA MATRIZ DE VISTA, NO EL CUBO
	 // Si se presiona la tecla ESC, se cierra la ventana
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.008f;
	 
	 // MODIFICANDO LAS KEYS PARA QUE FUNCIONEN CON CTRL + UP/DOWN
	 if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		 movY += 0.008f;
	 }
	 else if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.008f;


	 if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		 movY -= 0.008f;
	 }
	 else if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.008f;


	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.04f;
 }

