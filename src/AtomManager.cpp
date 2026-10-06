#include "AtomManager.h"

void AtomManager::addAtom(const Atom& atom){
    atoms.push_back(atom);
}

void AtomManager::drawAll(
    AtomRenderer& renderer,
    Shader& shader,
    glm::mat4 view,
    glm::mat4 projection,
    glm::vec3 cameraPosition
)
{
    for(const Atom& atom : atoms){
        renderer.draw(
            atom,
            shader,
            view,
            projection,
            cameraPosition
        );
    }

}