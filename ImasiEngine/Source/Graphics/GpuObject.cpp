#include "GpuObject.hpp"

#include "../Utils/Opengl.hpp"

namespace ImasiEngine
{
    GpuObject::GpuObject()
        : _id(UNSET)
    {
    }

    GpuObject::GpuObject(GpuObject&& gpuObject) noexcept
    {
        _id = gpuObject._id;
        gpuObject._id = UNSET;
    }

    GpuObject::~GpuObject()
    {
    }

    unsigned GpuObject::getId() const
    {
        return _id;
    }

    bool GpuObject::isValid() const
    {
        return _id != UNSET;
    }
}
