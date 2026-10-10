// Práctica 8. Materiales e iluminacion
// Hernández Castro Laura Isabel
// Fecha: 09/10/2026
// No. de cuenta: 320293634



    /*GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    unsigned char* image2;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    image = stbi_load("Models/Image_0.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    image2 = stbi_load("Models/Image_0.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);

    if (image2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image2);*/

    // Std. Includes
#include <string>
#include <iostream>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathematics
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
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400.0f, lastY = 300.0f;
bool firstMouse = true;

// Light & Orbit attributes
glm::vec3 lightPos(0.5f, 0.5f, 2.5f);  // Posición inicial
glm::vec3 sunPos(-2.5f, 2.0f, -1.0f);  // Posición inicial
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool activanim = false;

// Centro de la órbita (Posición del perro) y parámetros del círculo
glm::vec3 dogPos(-0.2f, 1.1f, 0.2f);
float orbitRadius = 2.5f;              // Radio de órbita idéntico para ambos
float movelightPos = 0.0f;             // Ángulo de rotación (en radianes)

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 8. Materiales e Iluminacion - Hernandez Castro Laura Isabel", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile shaders
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");

    // Load models
    Model perro((char*)"Models/RedDog.obj");
    Model pantalla((char*)"Models/SCREEN.obj");
    Model laptop((char*)"Models/Laptop.obj");
    Model teclado((char*)"Models/keyboard.obj");
    Model lata((char*)"Models/crushed_can.obj");
    Model silla((char*)"Models/chair.obj");
    Model mesa((char*)"Models/Office_Table.obj");
    Model luna((char*)"Models/Moon.obj");
    Model sol((char*)"Models/sun.obj");

    // ==============================================================
    // CARGA DE TEXTURAS (FUERA DEL BUCLE WHILE)
    // ==============================================================
    stbi_set_flip_vertically_on_load(true);
    int texWidth, texHeight, nrChannels;

    // --- 1. Textura de la Luna ---
    GLuint moonTexture;
    glGenTextures(1, &moonTexture);
    glBindTexture(GL_TEXTURE_2D, moonTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* moonImg = stbi_load("Models/Image_0.png", &texWidth, &texHeight, &nrChannels, 0);
    if (moonImg)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, moonImg);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(moonImg);
    }
    else
    {
        std::cout << "Error al cargar la textura de la luna (Models/Image_0.png)" << std::endl;
    }

    // --- 2. Textura del Sol ---
    GLuint sunTexture;
    glGenTextures(1, &sunTexture);
    glBindTexture(GL_TEXTURE_2D, sunTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* sunImg = stbi_load("Models/sun.jpg", &texWidth, &texHeight, &nrChannels, 0);
    if (sunImg)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, sunImg);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(sunImg);
    }
    else
    {
        std::cout << "Error al cargar la textura del sol (Models/sol.jpg)" << std::endl;
    }

    // Vértices del cubo indicador de luz
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

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = (GLfloat)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check events
        glfwPollEvents();
        DoMovement();

        // Clear buffers
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ==============================================================
        // CÁLCULO DE ÓRBITA CIRCULAR ALREDEDOR DEL PERRO
        // ==============================================================
        // Posición de la Luna en el círculo (X, Z)
        glm::vec3 currentLightPos;
        currentLightPos.x = dogPos.x + orbitRadius * cos(movelightPos);
        currentLightPos.y = dogPos.y + 1.0f; // Un poco por encima del perro
        currentLightPos.z = dogPos.z + orbitRadius * sin(movelightPos);

        // Posición del Sol (Desfasado 180 grados para estar opuesto)
        glm::vec3 currentSunPos;
        currentSunPos.x = dogPos.x + orbitRadius * cos(movelightPos + 3.14159265f);
        currentSunPos.y = dogPos.y + 1.0f;
        currentSunPos.z = dogPos.z + orbitRadius * sin(movelightPos + 3.14159265f);

        // ==============================================================
        // DIBUJADO DE MODELOS CON ILUMINACIÓN
        // ==============================================================
        lightingShader.Use();

        // Matrices View y Projection
        glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // --------------------------------------------------------
        // Luz de la LUNA (Fría / Neutra / Blanca)
        // --------------------------------------------------------
        glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.position"), currentLightPos.x, currentLightPos.y, currentLightPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.ambient"), 0.1f, 0.15f, 0.2f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.diffuse"), 0.4f, 0.5f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.specular"), 0.5f, 0.5f, 0.6f);

        // --------------------------------------------------------
        // Luz del SOL (Cálida / Amarillenta / Dorada)
        // --------------------------------------------------------
        glUniform3f(glGetUniformLocation(lightingShader.Program, "lightSun.position"), currentSunPos.x, currentSunPos.y, currentSunPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "lightSun.ambient"), 0.3f, 0.2f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "lightSun.diffuse"), 1.0f, 0.75f, 0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "lightSun.specular"), 1.0f, 0.9f, 0.6f);

        // Material general de los objetos
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.2f, 0.2f, 0.2f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.5f, 0.5f, 0.5f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

        // --- Perro ---
        glm::mat4 modelPerro = glm::mat4(1.0f);
        modelPerro = glm::translate(modelPerro, glm::vec3(-0.2f, 1.1f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPerro));
        perro.Draw(lightingShader);

        // --- Mesa ---
        glm::mat4 modelMesa = glm::mat4(1.0f);
        modelMesa = glm::rotate(modelMesa, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMesa = glm::translate(modelMesa, glm::vec3(0.0f, -0.5f, -1.0f));
        modelMesa = glm::scale(modelMesa, glm::vec3(1.5f, 1.5f, 1.5f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMesa));
        mesa.Draw(lightingShader);

        // --- Pantalla ---
        glm::mat4 modelPantalla = glm::mat4(1.0f);
        modelPantalla = glm::translate(modelPantalla, glm::vec3(-0.4f, 0.0f, 1.5f));
        modelPantalla = glm::rotate(modelPantalla, glm::radians(80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelPantalla = glm::scale(modelPantalla, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPantalla));
        pantalla.Draw(lightingShader);

        // --- Laptop ---
        glm::mat4 modelLaptop = glm::mat4(1.0f);
        modelLaptop = glm::translate(modelLaptop, glm::vec3(0.7f, 0.7f, 1.1f));
        modelLaptop = glm::rotate(modelLaptop, glm::radians(80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelLaptop = glm::scale(modelLaptop, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelLaptop));
        laptop.Draw(lightingShader);

        // --- Teclado ---
        glm::mat4 modelTeclado = glm::mat4(1.0f);
        modelTeclado = glm::translate(modelTeclado, glm::vec3(0.1f, 0.7f, 0.7f));
        modelTeclado = glm::scale(modelTeclado, glm::vec3(0.15f, 0.15f, 0.15f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelTeclado));
        teclado.Draw(lightingShader);

        // --- Lata ---
        glm::mat4 modelLata = glm::mat4(1.0f);
        modelLata = glm::translate(modelLata, glm::vec3(-0.6f, 0.66f, 0.7f));
        modelLata = glm::rotate(modelLata, glm::radians(110.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelLata = glm::scale(modelLata, glm::vec3(0.01f, 0.01f, 0.01f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelLata));
        lata.Draw(lightingShader);

        // --- Silla ---
        glm::mat4 modelSilla = glm::mat4(1.0f);
        modelSilla = glm::rotate(modelSilla, glm::radians(110.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelSilla = glm::scale(modelSilla, glm::vec3(0.05f, 0.05f, 0.05f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelSilla));
        silla.Draw(lightingShader);

        // ==============================================================
        // DIBUJADO DE EMISORES (LUNA Y SOL)
        // ==============================================================
        lampshader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // --- DIBUJAR LA LUNA ---
        glm::mat4 modelLamp = glm::mat4(1.0f);
        modelLamp = glm::translate(modelLamp, currentLightPos);
        modelLamp = glm::scale(modelLamp, glm::vec3(0.8f)); 
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelLamp));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, moonTexture);
        glUniform1i(glGetUniformLocation(lampshader.Program, "texture_diffuse1"), 0);

        luna.Draw(lampshader);

        glBindTexture(GL_TEXTURE_2D, 0);

        // --- DIBUJAR EL SOL ---
        glm::mat4 modelSun = glm::mat4(1.0f);
        modelSun = glm::translate(modelSun, currentSunPos);
        modelSun = glm::scale(modelSun, glm::vec3(0.2f)); // Cambiado de 0.3f a 0.2f para igualar tamaño
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelSun));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sunTexture);
        glUniform1i(glGetUniformLocation(lampshader.Program, "texture_diffuse1"), 0);

        sol.Draw(lampshader);

        glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(VAO);
        glBindVertexArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void DoMovement()
{
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

    if (activanim)
    {
        if (rot > -90.0f)
            rot -= 0.1f;
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
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

    if (keys[GLFW_KEY_O])
    {
        movelightPos += 2.5f * deltaTime; // Órbita en sentido horario
    }

    if (keys[GLFW_KEY_L])
    {
        movelightPos -= 2.5f * deltaTime; // Órbita en sentido antihorario
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = (GLfloat)xPos;
        lastY = (GLfloat)yPos;
        firstMouse = false;
    }

    GLfloat xOffset = (GLfloat)xPos - lastX;
    GLfloat yOffset = lastY - (GLfloat)yPos;

    lastX = (GLfloat)xPos;
    lastY = (GLfloat)yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}