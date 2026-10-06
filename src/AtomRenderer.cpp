#include "AtomRenderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

AtomRenderer::AtomRenderer(){
    
}

void AtomRenderer::draw(
    const Atom& atom, Shader& shader, 
    const glm::mat4 view, const glm::mat4 projection, 
    const glm::vec3 cameraPosition
)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, atom.getPosition());
    model = glm::scale(model, glm::vec3(atom.getRadius()));

    shader.use();

    shader.setMat4("model", glm::value_ptr(model));
    shader.setMat4("view", glm::value_ptr(view));
    shader.setMat4("projection", glm::value_ptr(projection));

    shader.setVec3("baseColor", atom.getColor());
    shader.setVec3("lightPosition", glm::vec3(2.0f, 2.0f, 3.0f));
    shader.setVec3("viewDirection", cameraPosition);

    atom.getSphere().draw();
}