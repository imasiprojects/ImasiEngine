#include "TransformationHelper.hpp"

#include <cmath>

namespace ImasiEngine
{
    namespace TransformationHelper
    {
        glm::vec2 rotate(const glm::vec3& direction)
        {
            return glm::vec2
            (
                glm::degrees(std::atan2f(direction.x, direction.z)),
                glm::degrees(std::asinf(direction.y))
            );
        }
    }
}

