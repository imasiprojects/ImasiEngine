#include "Entity.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace ImasiEngine
{
    Entity::Entity()
        : _model(nullptr)
        , _translationMatrix(1.f)
        , _position(0.f, 0.f, 0.f)
        , _rotationMatrix(1.f)
        , _rotation(0.f, 0.f, 0.f)
        , _scaleMatrix(1.f)
        , _scale(1.f, 1.f, 1.f)
        , _modelMatrix(1.f)
    {
    }

    Entity::~Entity()
    {
    }

    void Entity::invalidateTranslationMatrix() const
    {
        _translationMatrix.invalidateCache();
        _modelMatrix.invalidateCache();
    }

    void Entity::invalidateRotationMatrix() const
    {
        _rotationMatrix.invalidateCache();
        _modelMatrix.invalidateCache();
    }

    void Entity::invalidateScaleMatrix() const
    {
        _scaleMatrix.invalidateCache();
        _modelMatrix.invalidateCache();
    }

    Model* Entity::getModel() const
    {
        return _model;
    }

    void Entity::setModel(Model* model)
    {
        _model = model;
    }

    const glm::vec3& Entity::getPosition() const
    {
        return _position;
    }

    void Entity::setPosition(const glm::vec3& position)
    {
        _position = position;
        invalidateTranslationMatrix();
    }

    const glm::vec3& Entity::getRotation() const
    {
        return _rotation;
    }

    void Entity::setRotation(const glm::vec3& rotation)
    {
        _rotation = rotation;
        invalidateRotationMatrix();
    }

    const glm::vec3& Entity::getScale() const
    {
        return _scale;
    }

    void Entity::setScale(const glm::vec3& scale)
    {
        _scale = scale;
        invalidateScaleMatrix();
    }

    const glm::mat4& Entity::getModelMatrix() const
    {
        if (_modelMatrix.hasInvalidCache())
        {
            _modelMatrix = getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
            _modelMatrix.validateCache();
        }

        return _modelMatrix;
    }

    const glm::mat4& Entity::getTranslationMatrix() const
    {
        if (_translationMatrix.hasInvalidCache())
        {
            _translationMatrix = glm::translate(_position);
            _translationMatrix.validateCache();
        }

        return _translationMatrix;
    }

    const glm::mat4& Entity::getRotationMatrix() const
    {
        if (_rotationMatrix.hasInvalidCache())
        {
            glm::mat4 rotationMatrix(1.f);
            rotationMatrix = glm::rotate(rotationMatrix, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            rotationMatrix = glm::rotate(rotationMatrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            rotationMatrix = glm::rotate(rotationMatrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

            _rotationMatrix = rotationMatrix;
            _rotationMatrix.validateCache();
        }

        return _rotationMatrix;
    }

    const glm::mat4& Entity::getScaleMatrix() const
    {
        if (_scaleMatrix.hasInvalidCache())
        {
            _scaleMatrix = glm::scale(_scale);
            _scaleMatrix.validateCache();
        }

        return _scaleMatrix;
    }
}
