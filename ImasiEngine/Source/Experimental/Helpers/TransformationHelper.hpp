#ifndef IMASIENGINE_HELPERS_HPP
#define IMASIENGINE_HELPERS_HPP

#include <glm/glm.hpp>

namespace ImasiEngine
{
    namespace TransformationHelper
    {
        glm::vec2 getRotation(const glm::vec3& direction);
    }
}

#endif