#include "Atom.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Atom::Atom(const glm::vec3& position, float radius, const glm::vec3& color) 
           : position(position), color(color), radius(radius), sphere(std::make_shared<Sphere>(1.0f, 32, 16))
{
}

const glm::vec3& Atom::getPosition() const
{
    return position;
}

const glm::vec3& Atom::getColor() const
{
    return color;
}

float Atom::getRadius() const
{
    return radius;
}

const Sphere& Atom::getSphere() const
{
    return *sphere;
}

void Atom::draw(
        Shader& shader,
        const glm::mat4& view,
        const glm::mat4& projection,
        const glm::vec3& cameraPosition
)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(radius));
    
    shader.use();
    shader.setMat4("model", glm::value_ptr(model));
    shader.setMat4("view", glm::value_ptr(view));
    shader.setMat4("projection", glm::value_ptr(projection));
    shader.setVec3("baseColor", color);
    shader.setVec3("lightPosition", glm::vec3(2.0f, 2.0f, 3.0f));
    shader.setVec3("viewDirection", cameraPosition);

    sphere->draw();
}
