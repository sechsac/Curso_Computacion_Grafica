#version 330 core
layout (location = 0) in vec3 position; // se tienen las loc. de memoria de cada vector
layout (location = 1) in vec3 color;

out vec3 ourColor; // salida es un vector con información de color

void main()
{
    gl_Position = vec4(position, 1.0f); // se le da la posición y color para pasar a los fragmentos
    ourColor = color;
}