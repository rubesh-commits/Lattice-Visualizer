#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Sphere.h"
#include "AtomRenderer.h"
#include "AtomManager.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

int main(){
    if(!glfwInit()){
        std::cout << "GLFW is not initialized properly\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = 
        glfwCreateWindow(
            1280,
            720,
            "Atom Viewer",
            nullptr,
            nullptr
        );
    
    if(!window){
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))){
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader shader("../shaders/atom.vert", "../shaders/atom.frag");

    AtomRenderer atomRenderer;
    AtomManager atomManager;

    const int N = 4;                 // atoms per side (try 3 to 6)
    const float spacing = 1.2f;
    const float offset = (N - 1) * spacing / 2.0f;   // centres the lattice at the origin

    for (int x = 0; x < N; ++x)
      for (int y = 0; y < N; ++y)
          for (int z = 0; z < N; ++z)
              atomManager.addAtom(Atom(
                  glm::vec3(x * spacing - offset, y * spacing - offset, z * spacing - offset),
                  0.35f,
                  glm::vec3(0.2f, 0.6f, 1.0f)));

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 projection = 
        glm::perspective(
            glm::radians(45.0f),
            1280.0f / 720.0f,
            0.1f,
            100.0f
        );

    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );

    glViewport(0, 0, 1280, 720);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.05f, 0.05f, 0.08, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        float t = (float)glfwGetTime();
        glm::vec3 cameraPosition(9.0f * std::sin(t * 0.5f), 3.0f, 9.0f * std::cos(t * 0.5f));
        glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        shader.setVec3("lightPosition", glm::vec3(2.0f, 2.0f, 3.0f));
        shader.setVec3("viewPosition", cameraPosition);
        shader.setMat4("model", glm::value_ptr(model));
        shader.setMat4("view", glm::value_ptr(view));
        shader.setMat4("projection", glm::value_ptr(projection));

        atomManager.drawAll(atomRenderer, shader, view, projection, cameraPosition);
        /*atomRenderer.draw(oxygen, shader, view, projection, cameraPosition);

        atomRenderer.draw(hydrogen1, shader, view, projection, cameraPosition);

        atomRenderer.draw(hydrogen2, shader, view, projection, cameraPosition);*/

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}   
