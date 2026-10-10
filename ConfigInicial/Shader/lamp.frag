#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{
    // Renderiza la textura de la luna con su brillo propio
    color = texture(texture_diffuse1, TexCoords);
}