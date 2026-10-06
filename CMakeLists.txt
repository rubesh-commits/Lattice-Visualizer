cmake_minimum_required(VERSION 3.20)

project(AtomViewer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)

add_executable(AtomViewer
    src/main.cpp
    src/Sphere.cpp
    src/Shader.cpp
    src/Atom.cpp
    src/AtomRenderer.cpp
    src/AtomManager.cpp
    glad/src/glad.c
)

target_include_directories(AtomViewer PRIVATE
    glad/include
)

target_link_libraries(AtomViewer PRIVATE
    glfw
    GL
    m
)