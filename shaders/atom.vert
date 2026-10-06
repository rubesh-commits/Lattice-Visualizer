#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 WorldPosition;

void main(){
    vec4 worldPosition = model * vec4(aPosition, 1.0);

    WorldPosition = worldPosition.xyz;

    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * worldPosition;
}