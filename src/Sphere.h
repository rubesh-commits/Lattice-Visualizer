#pragma once

#include <glad/glad.h>

class Sphere
{
public:
    Sphere(float radius = 1.0f, int sectors = 32, int stacks = 16);
    ~Sphere();

    void draw() const;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    GLsizei indexCount;
};
