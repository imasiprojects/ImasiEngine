#ifndef IMASIENGINE_ENTITY_HPP
#define IMASIENGINE_ENTITY_HPP

#include <glm/glm.hpp>

#include "../Models/Model.hpp"
#include "../../Resources/Cached.hpp"

namespace ImasiEngine
{
    class Entity
    {
    private:

        Cached<glm::mat4> _modelMatrix;

        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale;

    public:

        Model* model;

        Entity();
        virtual ~Entity();

        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);

        const glm::vec3& getRotation() const;
        void setRotation(const glm::vec3& rotation);

        const glm::vec3& getScale() const;
        void setScale(const glm::vec3& scale);

        const glm::mat4& getModelMatrix();
    };
}

#endif
