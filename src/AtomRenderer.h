#pragma once

#include "Atom.h"
#include "Shader.h"

#include <glm/glm.hpp>

class AtomRenderer
{
public:
    AtomRenderer();

    void draw(const Atom& atom, Shader& shader, const glm::mat4 view, const glm::mat4 projection, const glm::vec3 cameraPosition);
};