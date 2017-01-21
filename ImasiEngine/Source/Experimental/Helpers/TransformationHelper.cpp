#include "TransformationHelper.hpp"

#include <cmath>
#include <glm/gtc/constants.hpp>

namespace ImasiEngine
{
    namespace TransformationHelper
    {
        glm::vec2 getRotation(const glm::vec3& direction)
        {
            return glm::vec2
            (
                std::asinf(direction.y),

                direction.x == 0 && direction.z == 0
                    ? 0
                    : std::atan2(direction.x, direction.z) + glm::pi<float>()
            );
        }

        glm::vec2 getRotation(const glm::vec3& from, const glm::vec3& to)
        {
            return getRotation(glm::normalize(to - from));
        }
    }
}

