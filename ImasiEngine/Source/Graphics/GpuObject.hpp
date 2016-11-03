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
    
        void setGpuObjectId(unsigned int id);
        void unsetGpuObjectId();

        virtual void createGpuObject() = 0;
        virtual void destroyGpuObject() = 0;
        virtual void resetGpuObject();

    public:

        unsigned int getGpuObjectId() const;
        virtual bool isValidGpuObject() const;
    };
}
