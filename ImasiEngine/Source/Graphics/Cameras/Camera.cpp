#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace ImasiEngine
{
    Camera::Camera()
        : _position(0.0f, 0.0f, 0.0f)
        , _rotationMatrix(glm::mat4(1.f))
        , _rotation(0.f, 0.f)
        , _viewMatrix(glm::mat4(1.f))
        , _fieldOfView(50.0f)
        , _aspectRatio(16.0f / 9.0f)
        , _nearPlaneDistance(0.01f)
        , _farPlaneDistance(1000.0f)
    {
    }

    Camera::~Camera()
    {
    }

    void Camera::invalidateRotationMatrix()
    {
        _rotationMatrix.invalidate();
        _viewMatrix.invalidate();
        _viewProjectionMatrix.invalidate();
    }

    void Camera::invalidateTranslationMatrix()
    {
        _translationMatrix.invalidate();
        _viewMatrix.invalidate();
        _viewProjectionMatrix.invalidate();
    }

    void Camera::invalidateViewMatrix()
    {
        _viewMatrix.invalidate();
        _viewProjectionMatrix.invalidate();
    }

    void Camera::invalidateProjectionMatrix()
    {
        _projectionMatrix.invalidate();
        _viewProjectionMatrix.invalidate();
    }

    void Camera::invalidateViewProjectionMatrix()
    {
        _viewProjectionMatrix.invalidate();
    }

    void Camera::fixAngles()
    {
        _rotation.x = std::fmod(_rotation.x, 360.0f);

        if (_rotation.x < 0.0f)
        {
            _rotation.x += 360.0f;
        }

        _rotation.y = glm::clamp(_rotation.y, -89.9f, 89.9f);
    }

    const glm::mat4& Camera::getTranslationMatrix()
    {
        if (!_translationMatrix.isValid())
        {
            _translationMatrix = glm::translate(glm::mat4(1.f), -_position);
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

    const glm::mat4& Camera::getRotationMatrix()
    {
        if (!_rotationMatrix.isValid())
        {
            glm::mat4 rotationMatrix(1.f);
            rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.y), glm::vec3(1.f, 0.f, 0.f));
            _rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_rotation.x), glm::vec3(0.f, 1.f, 0.f));
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

    void Camera::lookAt(const glm::vec3& objetive)
    {
        invalidateRotationMatrix();

        if (objetive == _position)
        {
            _rotation.x = 0.f;
            _rotation.y = 0.f;
        }
        else
        {
            glm::vec3 direction = glm::normalize(_position - objetive);
            _rotation.y = glm::degrees(std::asinf(direction.y));
            _rotation.x = -glm::degrees(std::atan2f(direction.x, direction.z));
        }

        fixAngles();
    }

    const glm::mat4& Camera::getViewMatrix()
    {
        if (!_viewMatrix.isValid())
        {
            _viewMatrix = getRotationMatrix() * getTranslationMatrix();
        }

        return _viewMatrix;
    }

    const glm::mat4& Camera::getProjectionMatrix()
    {
        if (!_projectionMatrix.isValid())
        {
            _projectionMatrix = glm::perspective(glm::radians(_fieldOfView), _aspectRatio, _nearPlaneDistance, _farPlaneDistance);
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

    const glm::mat4& Camera::getViewProjectionMatrix()
    {
        if (!_viewProjectionMatrix.isValid())
        {
            _viewProjectionMatrix = getProjectionMatrix() * getViewMatrix();
        }

        return _viewProjectionMatrix;
    }

    glm::vec3 Camera::getRelativeVector(const glm::vec3& direction)
    {
        return glm::vec3(glm::vec4(direction, 0.f) * getRotationMatrix());
    }

    glm::vec3 Camera::getForwardVector()
    {
        return getRelativeVector(glm::vec3(0.f, 0.f, -1.f));
    }

    glm::vec3 Camera::getBackwardVector()
    {
        return getRelativeVector(glm::vec3(0.f, 0.f, 1.f));
    }

    glm::vec3 Camera::getLeftVector()
    {
        return getRelativeVector(glm::vec3(-1.f, 0.f, 0.f));
    }

    glm::vec3 Camera::getRightVector()
    {
        return getRelativeVector(glm::vec3(1.f, 0.f, 0.f));
    }

    glm::vec3 Camera::getUpVector()
    {
        return getRelativeVector(glm::vec3(0.f, 1.f, 0.f));
    }

    glm::vec3 Camera::getDownVector()
    {
        return getRelativeVector(glm::vec3(0.f, -1.f, 0.f));
    }
}
