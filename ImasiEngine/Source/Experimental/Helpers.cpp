#include "Helpers.hpp"

#include <cmath>

namespace ImasiEngine
{
    namespace Helpers
    {
        glm::vec2 lookAt(const glm::vec3& from, const glm::vec3& to)
        {
            glm::vec3 direction = glm::normalize(from - to);
            return glm::vec2{
                glm::degrees(std::atan2f(direction.x, direction.z)),
                glm::degrees(std::asinf(direction.y))
            };
        }
    }
}

