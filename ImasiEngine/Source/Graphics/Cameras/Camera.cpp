#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/detail/type_mat.hpp>

namespace ImasiEngine
{
    Camera::Camera()
        : _mustUpdateTranslationMatrix(false)
        , _position(0.0f, 0.0f, 0.0f)
        , _mustUpdateRotationMatrix(false)
        , _rotationMatrix(glm::mat4(1.f))
        , _rotation(0.f, 0.f)
        , _mustUpdateViewMatrix(false)
        , _viewMatrix(glm::mat4(1.f))
        , _mustUpdateProjectionMatrix(true)
        , _fieldOfView(50.0f)
        , _aspectRatio(16.0f / 9.0f)
        , _nearPlaneDistance(0.01f)
        , _farPlaneDistance(1000.0f)
        , _mustUpdateViewProjectionMatrix(true)
    {
    }

    Camera::~Camera()
    {
    }

    void Camera::setMustUpdateRotationMatrix(const bool value)
    {
        if (value)
        {
            _mustUpdateRotationMatrix = true;
            _mustUpdateViewMatrix = true;
            _mustUpdateViewProjectionMatrix = true;
        }
        else
        {
            _mustUpdateRotationMatrix = false;
        }
    }

    void Camera::setMustUpdateTranslationMatrix(const bool value)
    {
        if (value)
        {
            _mustUpdateTranslationMatrix = true;
            _mustUpdateViewMatrix = true;
            _mustUpdateViewProjectionMatrix = true;
        }
        else
        {
            _mustUpdateTranslationMatrix = false;
        }
    }

    void Camera::setMustUpdateViewMatrix(const bool value)
    {
        if (value)
        {
            _mustUpdateViewMatrix = true;
            _mustUpdateViewProjectionMatrix = true;
        }
        else
        {
            _mustUpdateViewMatrix = false;
        }
    }

    void Camera::setMustUpdateProjectionMatrix(const bool value)
    {
        if (value)
        {
            _mustUpdateProjectionMatrix = true;
            _mustUpdateViewProjectionMatrix = true;
        }
        else
        {
            _mustUpdateProjectionMatrix = false;
        }
    }

    void Camera::setMustUpdateViewProjectionMatrix(const bool value)
    {
        _mustUpdateViewProjectionMatrix = value;
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
        if (_mustUpdateTranslationMatrix)
        {
            _translationMatrix = glm::translate(glm::mat4(1.f), -_position);
            setMustUpdateTranslationMatrix(false);
        }

        return _translationMatrix;
    }

    const glm::vec3& Camera::getPosition() const
    {
        return _position;
    }

    void Camera::setPosition(const glm::vec3& position)
    {
        setMustUpdateTranslationMatrix(true);
        _position = position;
    }

    void Camera::addPositionOffset(const glm::vec3& offset)
    {
        setMustUpdateTranslationMatrix(true);
        _position += offset;
    }

    const glm::mat4& Camera::getRotationMatrix()
    {
        if (_mustUpdateRotationMatrix)
        {
            _rotationMatrix = glm::mat4(1.f);
            _rotationMatrix = glm::rotate(_rotationMatrix, glm::radians(_rotation.y), glm::vec3(1.f, 0.f, 0.f));
            _rotationMatrix = glm::rotate(_rotationMatrix, glm::radians(_rotation.x), glm::vec3(0.f, 1.f, 0.f));

            setMustUpdateRotationMatrix(false);
        }

        return _rotationMatrix;
    }

    const glm::vec2& Camera::getRotation() const
    {
        return _rotation;
    }

    void Camera::setRotation(const glm::vec2& rotation)
    {
        setMustUpdateRotationMatrix(true);

        _rotation = rotation;
        fixAngles();
    }

    void Camera::addRotationOffset(const glm::vec2& offset)
    {
        setMustUpdateRotationMatrix(true);

        _rotation += offset;
        fixAngles();
    }

    void Camera::lookAt(const glm::vec3& objetive)
    {
        setMustUpdateRotationMatrix(true);

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
        if (_mustUpdateViewMatrix)
        {
            _viewMatrix = getRotationMatrix() * getTranslationMatrix();
            setMustUpdateViewMatrix(false);
        }

        return _viewMatrix;
    }

    const glm::mat4& Camera::getProjectionMatrix()
    {
        if (_mustUpdateProjectionMatrix)
        {
            _projectionMatrix = glm::perspective(glm::radians(_fieldOfView), _aspectRatio, _nearPlaneDistance, _farPlaneDistance);
            setMustUpdateProjectionMatrix(false);
        }

        return _projectionMatrix;
    }

    float Camera::getFieldOfView() const
    {
        return _fieldOfView;
    }

    void Camera::setFieldOfView(float fieldOfView)
    {
        setMustUpdateProjectionMatrix(true);
        _fieldOfView = glm::clamp(fieldOfView, 0.f, 180.f);
    }

    float Camera::getAspectRatio() const
    {
        return _aspectRatio;
    }

    void Camera::setAspectRatio(float aspectRatio)
    {
        setMustUpdateProjectionMatrix(true);
        _aspectRatio = glm::max(0.f, aspectRatio);
    }

    float Camera::getNearPlaneDistance() const
    {
        return _nearPlaneDistance;
    }

    void Camera::setNearPlaneDistance(float nearPlaneDistance)
    {
        setMustUpdateProjectionMatrix(true);
        _nearPlaneDistance = nearPlaneDistance;
    }

    float Camera::getFarPlaneDistance() const
    {
        return _farPlaneDistance;
    }

    void Camera::setFarPlaneDistance(float farPlaneDistance)
    {
        setMustUpdateProjectionMatrix(true);
        _farPlaneDistance = farPlaneDistance;
    }

    void Camera::setPlaneDistances(float nearPlaneDistance, float farPlaneDistance)
    {
        setMustUpdateProjectionMatrix(true);
        _nearPlaneDistance = nearPlaneDistance;
        _farPlaneDistance = farPlaneDistance;
    }

    const glm::mat4& Camera::getViewProjectionMatrix()
    {
        if (_mustUpdateViewProjectionMatrix)
        {
            _viewProjectionMatrix = getProjectionMatrix() * getViewMatrix();
            setMustUpdateViewProjectionMatrix(false);
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
