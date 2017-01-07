#ifndef IMASIENGINE_ENTITY_HPP
#define IMASIENGINE_ENTITY_HPP

#include <glm/glm.hpp>

#include "../Models/Model.hpp"
#include "../../Resources/Cache.hpp"

namespace ImasiEngine
{
    class Entity
    {
    private:

        Model* _model;

        mutable Cache<glm::mat4> _translationMatrix;
        glm::vec3 _position;
        mutable Cache<glm::mat4> _rotationMatrix;
        glm::vec3 _rotation;
        mutable Cache<glm::mat4> _scaleMatrix;
        glm::vec3 _scale;

        mutable Cache<glm::mat4> _modelMatrix;

        void invalidateTranslationMatrix() const;
        void invalidateRotationMatrix() const;
        void invalidateScaleMatrix() const;

    public:

        Entity();
        virtual ~Entity();

        Model* getModel() const;
        void setModel(Model* model);

        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);

        const glm::vec3& getRotation() const;
        void setRotation(const glm::vec3& rotation);

        const glm::vec3& getScale() const;
        void setScale(const glm::vec3& scale);

        const glm::mat4& getTranslationMatrix() const;
        const glm::mat4& getRotationMatrix() const;
        const glm::mat4& getScaleMatrix() const;
        const glm::mat4& getModelMatrix() const;
    };
}

#endif
