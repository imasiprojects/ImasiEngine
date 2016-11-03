#include "GpuObject.hpp"

#include "../Utils/Opengl.hpp"

namespace ImasiEngine
{
    GpuObject::GpuObject()
        : _gpuId(NULL_ID)
    {
    }

    GpuObject::GpuObject(GpuObject&& gpuObject) noexcept
        : _gpuId(gpuObject._gpuId)
    {
        gpuObject.unsetGpuObjectId();
    }

    GpuObject::~GpuObject()
    {
    }

    void GpuObject::setGpuObjectId(unsigned int id)
    {
        _gpuId = id;
    }

    void GpuObject::unsetGpuObjectId()
    {
        _gpuId = NULL_ID;
    }

    void GpuObject::resetGpuObject()
    {
        if (isValidGpuObject())
        {
            destroyGpuObject();
        }

        createGpuObject();
    }

    unsigned int GpuObject::getGpuObjectId() const
    {
        return _gpuId;
    }

    bool GpuObject::isValidGpuObject() const
    {
        return _gpuId != NULL_ID;
    }
}
