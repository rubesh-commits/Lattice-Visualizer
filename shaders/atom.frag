#version 460 core

in vec3 Normal;
in vec3 WorldPosition;

out vec4 FragColor;

uniform vec3 baseColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

void main(){        
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * baseColor;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPosition - WorldPosition);
    float diffuseStrength = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diffuseStrength * baseColor;

    vec3 viewDirection = normalize(viewPosition - WorldPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularStrength = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32.0);
    vec3 specular = vec3(1.0) * specularStrength;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}