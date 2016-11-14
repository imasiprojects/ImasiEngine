#ifndef IMASIENGINE_ENTITY_HPP
#define IMASIENGINE_ENTITY_HPP

#include <glm/glm.hpp>

#include "Model.hpp"

namespace ImasiEngine
{
    class Entity
    {
    private:

        bool _mustUpdateModelMatrix;
        glm::mat4 _modelMatrix;

        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale;

    public:

        Model* model;

        Entity();
        virtual ~Entity();

        glm::vec3 getPosition() const;
        void setPosition(glm::vec3& position);

        glm::vec3 getRotation() const;
        void setRotation(glm::vec3& rotation);

        glm::vec3 getScale() const;
        void setScale(glm::vec3& scale);

        glm::mat4 getModelMatrix();
    };
}

#endif
