#include "Camera.hpp"

#include <glm/glm.hpp>

#include "../../Experimental/Helpers/TransformationHelper.hpp"

namespace ImasiEngine
{
    Camera::Camera()
        : _position(0.0f, 0.0f, 0.0f)
        , _rotationMatrix(1.f)
        , _rotation(0.f, 0.f)
        , _viewMatrix(1.f)
        , _fieldOfView(50.0f)
        , _aspectRatio(1.f)
        , _nearPlaneDistance(0.01f)
        , _farPlaneDistance(1000.0f)
    {
        _projectionMatrix.invalidateCache();
        _viewProjectionMatrix.invalidateCache();
    }

    Camera::~Camera()
    {
    }

    void Camera::invalidateRotationMatrix() const
    {
        _rotationMatrix.invalidateCache();
        _viewMatrix.invalidateCache();
        _viewProjectionMatrix.invalidateCache();
    }

    void Camera::invalidateTranslationMatrix() const
    {
        _translationMatrix.invalidateCache();
        _viewMatrix.invalidateCache();
        _viewProjectionMatrix.invalidateCache();
    }

    void Camera::invalidateViewMatrix() const
    {
        _viewMatrix.invalidateCache();
        _viewProjectionMatrix.invalidateCache();
    }

    void Camera::invalidateProjectionMatrix() const
    {
        _projectionMatrix.invalidateCache();
        _viewProjectionMatrix.invalidateCache();
    }

    void Camera::fixAngles()
    {
        _rotation.y = std::fmod(_rotation.y, glm::two_pi<float>());

        if (_rotation.y < 0.0f)
        {
            _rotation.y += glm::two_pi<float>();
        }

        static const float limitX = glm::half_pi<float>() - glm::epsilon<float>();
        _rotation.x = glm::clamp(_rotation.x, -limitX, limitX);
    }

    const glm::mat4& Camera::getTranslationMatrix() const
    {
        if (_translationMatrix.hasInvalidCache())
        {
            _translationMatrix = glm::translate(glm::mat4(1.f), -_position);
            _translationMatrix.validateCache();
        }

        return _translationMatrix;
    }

    const glm::vec3& Camera::getPosition() const
    {
        return _position;
    }

    void Camera::setPosition(const glm::vec3& position)
    {
        invalidateTranslationMatrix();
        _position = position;
    }

    void Camera::addPositionOffset(const glm::vec3& offset)
    {
        invalidateTranslationMatrix();
        _position += offset;
    }

    const glm::mat4& Camera::getRotationMatrix() const
    {
        if (_rotationMatrix.hasInvalidCache())
        {
            glm::mat4 rotationMatrix(1.f);

            rotationMatrix = glm::rotate(rotationMatrix, _rotation.x, glm::vec3(1.f, 0.f, 0.f));
            _rotationMatrix = glm::rotate(rotationMatrix, _rotation.y, glm::vec3(0.f, 1.f, 0.f));

            _rotationMatrix.validateCache();
        }

        return _rotationMatrix;
    }

    const glm::vec2& Camera::getRotation() const
    {
        return _rotation;
    }

    void Camera::setRotation(const glm::vec2& rotation)
    {
        invalidateRotationMatrix();

        _rotation = rotation;
        fixAngles();
    }

    void Camera::addRotationOffset(const glm::vec2& offset)
    {
        invalidateRotationMatrix();

        _rotation += offset;
        fixAngles();
    }

    void Camera::lookAt(const glm::vec3& objective)
    {
        invalidateRotationMatrix();

        if (objective == _position)
        {
            _rotation.x = 0.f;
            _rotation.y = 0.f;
        }
        else
        {
            // Inverse rotation
            _rotation = -TransformationHelper::getRotation(_position, objective);
        }

        fixAngles();
    }

    const glm::mat4& Camera::getViewMatrix() const
    {
        if (_viewMatrix.hasInvalidCache())
        {
            _viewMatrix = getRotationMatrix() * getTranslationMatrix();
            _viewMatrix.validateCache();
        }

        return _viewMatrix;
    }

    const glm::mat4& Camera::getProjectionMatrix() const
    {
        if (_projectionMatrix.hasInvalidCache())
        {
            _projectionMatrix = glm::perspective(glm::radians(_fieldOfView), _aspectRatio, _nearPlaneDistance, _farPlaneDistance);
            _projectionMatrix.validateCache();
        }

        return _projectionMatrix;
    }

    float Camera::getFieldOfView() const
    {
        return _fieldOfView;
    }

    void Camera::setFieldOfView(float fieldOfView)
    {
        invalidateProjectionMatrix();
        _fieldOfView = glm::clamp(fieldOfView, 0.f, 180.f);
    }

    float Camera::getAspectRatio() const
    {
        return _aspectRatio;
    }

    void Camera::setAspectRatio(float aspectRatio)
    {
        invalidateProjectionMatrix();
        _aspectRatio = glm::max(0.f, aspectRatio);
    }

    float Camera::getNearPlaneDistance() const
    {
        return _nearPlaneDistance;
    }

    void Camera::setNearPlaneDistance(float nearPlaneDistance)
    {
        invalidateProjectionMatrix();
        _nearPlaneDistance = nearPlaneDistance;
    }

    float Camera::getFarPlaneDistance() const
    {
        return _farPlaneDistance;
    }

    void Camera::setFarPlaneDistance(float farPlaneDistance)
    {
        invalidateProjectionMatrix();
        _farPlaneDistance = farPlaneDistance;
    }

    void Camera::setPlaneDistances(float nearPlaneDistance, float farPlaneDistance)
    {
        invalidateProjectionMatrix();
        _nearPlaneDistance = nearPlaneDistance;
        _farPlaneDistance = farPlaneDistance;
    }

    const glm::mat4& Camera::getViewProjectionMatrix() const
    {
        if (_viewProjectionMatrix.hasInvalidCache())
        {
            _viewProjectionMatrix = getProjectionMatrix() * getViewMatrix();
            _viewProjectionMatrix.validateCache();
        }

        return _viewProjectionMatrix;
    }

    glm::vec3 Camera::getRelativeVector(const glm::vec3& direction) const
    {
        return glm::vec3(glm::vec4(direction, 0.f) * getRotationMatrix());
    }

    glm::vec3 Camera::getForwardVector() const
    {
        return getRelativeVector(glm::vec3(0.f, 0.f, -1.f));
    }

    glm::vec3 Camera::getBackwardVector() const
    {
        return getRelativeVector(glm::vec3(0.f, 0.f, 1.f));
    }

    glm::vec3 Camera::getLeftVector() const
    {
        return getRelativeVector(glm::vec3(-1.f, 0.f, 0.f));
    }

    glm::vec3 Camera::getRightVector() const
    {
        return getRelativeVector(glm::vec3(1.f, 0.f, 0.f));
    }

    glm::vec3 Camera::getUpVector() const
    {
        return getRelativeVector(glm::vec3(0.f, 1.f, 0.f));
    }

    glm::vec3 Camera::getDownVector() const
    {
        return getRelativeVector(glm::vec3(0.f, -1.f, 0.f));
    }
}
