#ifndef IMASIENGINE_HELPERS_HPP
#define IMASIENGINE_HELPERS_HPP

#include <glm/glm.hpp>

namespace ImasiEngine
{
    namespace Helpers
    {
        glm::vec2 lookAt(const glm::vec3& from, const glm::vec3& to);
    }
}

#endif