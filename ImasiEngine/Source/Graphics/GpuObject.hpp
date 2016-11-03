#pragma once

namespace ImasiEngine
{
    class GpuObject
    {
    private:

        unsigned int _gpuId;

    protected:

        GpuObject();
        GpuObject(const GpuObject&) = delete;
        GpuObject(GpuObject&& gpuObject) noexcept;
        virtual ~GpuObject();
    
        void setGpuId(unsigned int id);
        void unsetGpuId();

        virtual void createGpuObject() = 0;
        virtual void destroyGpuObject() = 0;
        virtual void resetGpuObject();

    public:

        unsigned int getGpuId() const;

        virtual bool isValidGpuId() const;
    };
}
