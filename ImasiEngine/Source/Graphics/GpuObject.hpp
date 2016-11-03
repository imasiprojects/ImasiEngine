#pragma once

namespace ImasiEngine
{
    class GpuObject
    {
    protected:

        unsigned int _id;

        GpuObject();
        GpuObject(const GpuObject&) = delete;
        GpuObject(GpuObject&& gpuObject) noexcept;
        virtual ~GpuObject();
    
    public:

        unsigned int getId() const;

        virtual bool isValid() const;
        virtual void invalidate();
    };
}