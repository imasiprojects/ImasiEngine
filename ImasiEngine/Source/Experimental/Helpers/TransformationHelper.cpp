#include "TransformationHelper.hpp"

#include <cmath>
#include <glm/gtc/constants.hpp>
#include "../../Exceptions/InvalidArgumentException.hpp"

namespace ImasiEngine
{
    namespace TransformationHelper
    {
        glm::vec2 getRotation(const glm::vec3& direction)
        {
            if (direction.y < -1.f || direction.y > 1.f)
            {
                throw InvalidArgumentException("direction.y", "Must be in range [-1, 1]");
            }

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

