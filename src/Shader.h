#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
private:
    GLuint ID;
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use() const;
    void setMat4(const std::string& name, const float* value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
};


