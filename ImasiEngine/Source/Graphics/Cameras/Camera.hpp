#ifndef IMASIENGINE_CAMERA_HPP
#define IMASIENGINE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace ImasiEngine
{
    class Camera
    {
    private:

        bool _mustUpdateTranslationMatrix;
        void setMustUpdateTranslationMatrix();
        glm::mat4 _translationMatrix;
        glm::vec3 _position;

        bool _mustUpdateRotationMatrix;
        void setMustUpdateRotationMatrix();
        glm::mat4 _rotationMatrix;
        glm::vec2 _rotation;

        bool _mustUpdateViewMatrix;
        glm::mat4 _viewMatrix;

        bool _mustUpdateProjectionMatrix;
        void setMustUpdateProjectionMatrix();
        glm::mat4 _projectionMatrix;
        float _fieldOfView;
        float _aspectRatio;
        float _nearPlaneDistance;
        float _farPlaneDistance;

        bool _mustUpdateViewProjectionMatrix;
        glm::mat4 _viewProjectionMatrix;

        void fixAngles();

    public:

        Camera();
        ~Camera();

        glm::mat4 getTranslationMatrix();
        glm::vec3 getPosition() const;
        void setPosition(glm::vec3& position);
        void addPositionOffset(glm::vec3& offset);

        glm::mat4 getRotationMatrix();
        glm::vec2 getRotation() const;
        void setRotation(glm::vec2& rotation);
        void addRotationOffset(glm::vec2& offset);
        void lookAt(glm::vec3 objetive);

        glm::mat4 getViewMatrix();

        glm::mat4 getProjectionMatrix();
        float getFieldOfView() const;
        void setFieldOfView(float fieldOfView);
        float getAspectRatio() const;
        void setAspectRatio(float aspectRatio);
        float getNearPlaneDistance() const;
        void setNearPlaneDistance(float nearPlaneDistance);
        float getFarPlaneDistance() const;
        void setFarPlaneDistance(float farPlaneDistance);
        void setPlaneDistances(float nearPlaneDistance, float farPlaneDistance);

        glm::mat4 getViewProjectionMatrix();

        glm::vec3 getRelativeVector(glm::vec3& direction);
        glm::vec3 getForwardVector();
        glm::vec3 getBackwardVector();
        glm::vec3 getLeftVector();
        glm::vec3 getRightVector();
        glm::vec3 getUpVector();
        glm::vec3 getDownVector();
    };
}

#endif
