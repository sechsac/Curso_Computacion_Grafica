// Práctica 6. Carga de modelos y cámara sintética
// Hernández Castro Laura Isabel
// Fecha: 21/09/2026
// No. de cuenta: 320293634




// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) ); // poniéndolo en 0,0,0 aparenta estar dentro del modelo
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;



int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Practica 6. Carga de modelos y camara sintetica - Hernandez Castro Laura Isabel", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    
    // Load models
    // Se carga el modelo 3D
    // Añadiendo un nuevo modelo
    
    Model perro((char*)"Models/RedDog.obj"); // sólo se carga el modelo porque dentro lleva el material, y en el material viene la textura
    Model pantalla((char*)"Models/SCREEN.obj");
    Model laptop((char*)"Models/Laptop.obj");
	Model teclado((char*)"Models/keyboard.obj");
	Model lata((char*)"Models/crushed_can.obj");
    Model mesa((char*)"Models/Office_Table.obj"); // sólo se carga el modelo porque dentro lleva el material, y en el material viene la textura
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
  

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 modelPerro = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPerro));
        perro.Draw(shader);

        // Aplicando las transformaciones previamente vistas al modelo
        glm::mat4 modelMesa = glm::mat4(1.0f);
        modelMesa = glm::rotate(modelMesa, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMesa = glm::translate(modelMesa, glm::vec3(0.0f, -0.5f, -1.0f));
        modelMesa = glm::scale(modelMesa, glm::vec3(1.5f, 1.5f, 1.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMesa));
        mesa.Draw(shader);

        // Dibujando la pantalla
        glm::mat4 modelPantalla = glm::mat4(1.0f);
        modelPantalla = glm::translate(modelPantalla, glm::vec3(-0.4f, 0.0f, 1.5f));
        modelPantalla = glm::rotate(modelPantalla, glm::radians(80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelPantalla = glm::scale(modelPantalla, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPantalla));
        pantalla.Draw(shader);

        // Dibujando la laptop
        glm::mat4 modelLaptop = glm::mat4(1.0f);
        modelLaptop = glm::translate(modelLaptop, glm::vec3(0.7f, 0.7f, 1.1f));
        modelLaptop = glm::rotate(modelLaptop, glm::radians(100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelLaptop = glm::scale(modelLaptop, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelLaptop));
        laptop.Draw(shader);

		// Dibujando el teclado
        glm::mat4 modelTeclado = glm::mat4(1.0f);
        modelTeclado = glm::translate(modelTeclado, glm::vec3(0.1f, 0.7f, 0.7f));
        //modelTeclado = glm::rotate(modelTeclado, glm::radians(80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelTeclado = glm::scale(modelTeclado, glm::vec3(0.15f, 0.15f, 0.15f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelTeclado));
        teclado.Draw(shader);

		// Dibujando la lata
        glm::mat4 modelLata = glm::mat4(1.0f);
        modelLata = glm::translate(modelLata, glm::vec3(-0.6f, 0.65f, 0.7f));
        modelLata = glm::rotate(modelLata, glm::radians(110.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelLata = glm::scale(modelLata, glm::vec3(0.01f, 0.01f, 0.01f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelLata));
        lata.Draw(shader);


        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

 

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

