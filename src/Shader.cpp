#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

static std::string readFile(const char* path){
    std::ifstream file(path);

    if(!file.is_open()){
        std::cerr << "Failed to open shader: " << path << '\n';

        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(
        vertexShader,
        1,
        &vertexSource,
        nullptr
    );
    glCompileShader(vertexShader);

    GLint success;

    glGetShaderiv(
        vertexShader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(
            vertexShader,
            512,
            nullptr,
            infoLog
        );

        std::cerr
            << "Vertex shader compilation failed:\n"
            << infoLog << '\n';
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(
        fragmentShader,
        1,
        &fragmentSource,
        nullptr
    );
    glCompileShader(fragmentShader);

    glGetShaderiv(
        fragmentShader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(
            fragmentShader,
            512,
            nullptr,
            infoLog
        );

        std::cerr
            << "Fragment shader compilation failed:\n"
            << infoLog << '\n';
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    
    glGetProgramiv(
        ID,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetProgramInfoLog(
            ID,
            512,
            nullptr,
            infoLog
        );

        std::cerr
            << "Shader program linking failed:\n"
            << infoLog << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader(){
    glDeleteProgram(ID);
}

void Shader::use() const{
    glUseProgram(ID);
}

void Shader::setMat4(const std::string& name, const float* value) const{
    GLuint location = glGetUniformLocation(ID, name.c_str());

    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const{
    GLint location = glGetUniformLocation(ID, name.c_str());

    glUniform3fv(
        location,
        1,
        &value[0]  
    );
}