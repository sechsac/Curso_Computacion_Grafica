#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    float shininess;
};

uniform vec3 viewPos;
uniform Light lightMoon;
uniform Light lightSun;
uniform Material material;

uniform sampler2D texture_diffuse1; // <--- Textura del modelo .obj

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 texColor)
{
    // Ambient
    vec3 ambient = light.ambient * texColor;
    
    // Diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * texColor);
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec;
    
    return (ambient + diffuse + specular);
}

void main()
{
    // Obtener el color original de la textura del objeto
    vec3 texColor = vec3(texture(texture_diffuse1, TexCoords));
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Calcular luz combinada sobre la textura
    vec3 result = CalcPointLight(lightMoon, Normal, FragPos, viewDir, texColor);
    result += CalcPointLight(lightSun, Normal, FragPos, viewDir, texColor);
    
    FragColor = vec4(result, 1.0);
}