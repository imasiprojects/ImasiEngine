#include "Entity.hpp"

#include <glm/gtx/transform.hpp>

namespace ImasiEngine
{
    Entity::Entity()
        : _mustUpdateModelMatrix(false)
        , _modelMatrix(glm::mat4(1.f))
        , _position(glm::vec3(0.f, 0.f, 0.f))
        , _rotation(glm::vec3(0.f, 0.f, 0.f))
        , _scale(glm::vec3(1.f, 1.f, 1.f))
        , model(nullptr)
    {
    }

    Entity::~Entity()
    {
    }

    glm::vec3 Entity::getPosition() const
    {
        return _position;
    }

    void Entity::setPosition(glm::vec3& position)
    {
        _mustUpdateModelMatrix = true;
        _position = position;
    }

    glm::vec3 Entity::getRotation() const
    {
        return _rotation;
    }

    void Entity::setRotation(glm::vec3& rotation)
    {
        _mustUpdateModelMatrix = true;
        _rotation = rotation;
    }

    glm::vec3 Entity::getScale() const
    {
        return _scale;
    }

    void Entity::setScale(glm::vec3& scale)
    {
        _mustUpdateModelMatrix = true;
        _scale = scale;
    }

    glm::mat4 Entity::getModelMatrix()
    {
        if (_mustUpdateModelMatrix)
        {
            glm::mat4 rotationMatrix(1.f);
            rotationMatrix = glm::rotate(rotationMatrix, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            rotationMatrix = glm::rotate(rotationMatrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            rotationMatrix = glm::rotate(rotationMatrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

            _modelMatrix = glm::translate(_position) * rotationMatrix * glm::scale(_scale);
            _mustUpdateModelMatrix = false;
        }

        return _modelMatrix;
    }
}
