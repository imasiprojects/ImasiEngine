#include "GpuObject.hpp"

#include "../Utils/Opengl.hpp"

namespace ImasiEngine
{
    GpuObject::GpuObject()
        : _gpuId(UNSET)
    {
    }

    GpuObject::GpuObject(GpuObject&& gpuObject) noexcept
        : _gpuId(gpuObject._gpuId)
    {
        gpuObject.unsetGpuId();
    }

    GpuObject::~GpuObject()
    {
    }

    void GpuObject::setGpuId(unsigned int id)
    {
        _gpuId = id;
    }

    void GpuObject::unsetGpuId()
    {
        _gpuId = UNSET;
    }

    void GpuObject::resetGpuObject()
    {
        if (isValidGpuId())
        {
            destroyGpuObject();
        }

        createGpuObject();
    }

    unsigned GpuObject::getGpuId() const
    {
        return _gpuId;
    }

    bool GpuObject::isValidGpuId() const
    {
        return _gpuId != UNSET;
    }
}
