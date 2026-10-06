#include "Sphere.h"

#include <cmath>
#include <vector>

struct Vertex{
    float x, y, z;
    float nx, ny, nz;
};

Sphere::Sphere(float radius, int sectors, int stacks){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    const float PI = 3.14159265359f;

    for(int stack = 0; stack <= stacks; ++stack){
        float stackAngle = PI / 2.0f - stack * PI / stacks;

        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);

        for(int sector = 0; sector <= sectors; ++sector){
            float sectorAngle = sector  * 2.0f * PI / sectors;

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            Vertex vertex;

            vertex.x = x;
            vertex.y = y;
            vertex.z = z;

            vertex.nx = x / radius;
            vertex.ny = y / radius;
            vertex.nz = z / radius;

            vertices.push_back(vertex);
        }
    }

    for(int stack = 0; stack < stacks; ++stack){
        int first = stack * (sectors + 1);
        int second = first + sectors + 1;

        for(int sector = 0; sector < sectors; ++sector){
            indices.push_back(first + sector);
            indices.push_back(second + sector);
            indices.push_back(first + sector + 1);

            indices.push_back(second + sector);
            indices.push_back(second + sector + 1);
            indices.push_back(first + sector + 1);
        }
    }

    indexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Sphere::~Sphere(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Sphere::draw() const{
    glBindVertexArray(VAO);
    
    glDrawElements(
        GL_TRIANGLES,
        indexCount,
        GL_UNSIGNED_INT,
        nullptr
    );

    glBindVertexArray(0);
}