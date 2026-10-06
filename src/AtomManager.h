#pragma once

#include <vector>

#include "Atom.h"
#include "AtomRenderer.h"

class AtomManager
{
private:
    std::vector<Atom> atoms;
public:
    void addAtom(const Atom& atom);

    void drawAll(
        AtomRenderer& renderer,
        Shader& shader,
        glm::mat4 view,
        glm::mat4 projection,
        glm::vec3 cameraPosition
    );
};