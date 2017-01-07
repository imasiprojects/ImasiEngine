#ifndef IMASIENGINE_CAMERA_HPP
#define IMASIENGINE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../../Resources/Cache.hpp"

namespace ImasiEngine
{
    class Camera
    {
    private:

        mutable Cache<glm::mat4> _translationMatrix;
        glm::vec3 _position;

        mutable Cache<glm::mat4> _rotationMatrix;
        glm::vec2 _rotation;

        mutable Cache<glm::mat4> _viewMatrix;

        mutable Cache<glm::mat4> _projectionMatrix;
        float _fieldOfView;
        float _aspectRatio;
        float _nearPlaneDistance;
        float _farPlaneDistance;

        mutable Cache<glm::mat4> _viewProjectionMatrix;

        void invalidateTranslationMatrix() const;
        void invalidateRotationMatrix() const;
        void invalidateViewMatrix() const;
        void invalidateProjectionMatrix() const;

        void fixAngles();

    public:

        Camera();
        ~Camera();

        const glm::mat4& getTranslationMatrix() const;
        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);
        void addPositionOffset(const glm::vec3& offset);

        const glm::mat4& getRotationMatrix() const;
        const glm::vec2& getRotation() const;
        void setRotation(const glm::vec2& rotation);
        void addRotationOffset(const glm::vec2& offset);
        void lookAt(const glm::vec3& objetive);

        const glm::mat4& getViewMatrix() const;

        const glm::mat4& getProjectionMatrix() const;
        float getFieldOfView() const;
        void setFieldOfView(float fieldOfView);
        float getAspectRatio() const;
        void setAspectRatio(float aspectRatio);
        float getNearPlaneDistance() const;
        void setNearPlaneDistance(float nearPlaneDistance);
        float getFarPlaneDistance() const;
        void setFarPlaneDistance(float farPlaneDistance);
        void setPlaneDistances(float nearPlaneDistance, float farPlaneDistance);

        const glm::mat4& getViewProjectionMatrix() const;

        glm::vec3 getRelativeVector(const glm::vec3& direction) const;
        glm::vec3 getForwardVector() const;
        glm::vec3 getBackwardVector() const;
        glm::vec3 getLeftVector() const;
        glm::vec3 getRightVector() const;
        glm::vec3 getUpVector() const;
        glm::vec3 getDownVector() const;
    };
}

#endif
