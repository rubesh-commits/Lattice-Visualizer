#pragma once
#include <memory>
#include <glm/glm.hpp>

#include "Sphere.h"
#include "Shader.h"

class Atom
{
private:
    glm::vec3 position;
    glm::vec3 color;
    float radius;

    std::shared_ptr<Sphere> sphere;
public:
    Atom(
        const glm::vec3& position,
        float radius,
        const glm::vec3& color
    );

    void draw(
        Shader& shader,
        const glm::mat4& view,
        const glm::mat4& projection,
        const glm::vec3& cameraPosition
    );
    
    const glm::vec3& getPosition() const;
    const glm::vec3& getColor() const;
    float getRadius() const;
    const Sphere& getSphere() const;
};
