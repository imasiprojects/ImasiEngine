#ifndef IMASIENGINE_CAMERA_HPP
#define IMASIENGINE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../../Resources/Cached.hpp"

namespace ImasiEngine
{
    class Camera
    {
    private:

        Cached<glm::mat4> _translationMatrix;
        glm::vec3 _position;

        Cached<glm::mat4> _rotationMatrix;
        glm::vec2 _rotation;

        Cached<glm::mat4> _viewMatrix;

        Cached<glm::mat4> _projectionMatrix;
        float _fieldOfView;
        float _aspectRatio;
        float _nearPlaneDistance;
        float _farPlaneDistance;

        mutable Cached<glm::mat4> _viewProjectionMatrix;

        void invalidateTranslationMatrix();
        void invalidateRotationMatrix();
        void invalidateViewMatrix();
        void invalidateProjectionMatrix();
        void invalidateViewProjectionMatrix();

        void fixAngles();

    public:

        Camera();
        ~Camera();

        const glm::mat4& getTranslationMatrix();
        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);
        void addPositionOffset(const glm::vec3& offset);

        const glm::mat4& getRotationMatrix();
        const glm::vec2& getRotation() const;
        void setRotation(const glm::vec2& rotation);
        void addRotationOffset(const glm::vec2& offset);
        void lookAt(const glm::vec3& objetive);

        const glm::mat4& getViewMatrix();

        const glm::mat4& getProjectionMatrix();
        float getFieldOfView() const;
        void setFieldOfView(float fieldOfView);
        float getAspectRatio() const;
        void setAspectRatio(float aspectRatio);
        float getNearPlaneDistance() const;
        void setNearPlaneDistance(float nearPlaneDistance);
        float getFarPlaneDistance() const;
        void setFarPlaneDistance(float farPlaneDistance);
        void setPlaneDistances(float nearPlaneDistance, float farPlaneDistance);

        const glm::mat4& getViewProjectionMatrix();

        glm::vec3 getRelativeVector(const glm::vec3& direction);
        glm::vec3 getForwardVector();
        glm::vec3 getBackwardVector();
        glm::vec3 getLeftVector();
        glm::vec3 getRightVector();
        glm::vec3 getUpVector();
        glm::vec3 getDownVector();
    };
}

#endif
