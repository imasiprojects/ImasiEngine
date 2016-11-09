#ifndef IMASIENGINE_GLOBJECT_HPP
#define IMASIENGINE_GLOBJECT_HPP

namespace ImasiEngine
{
    class GLObject
    {
    private:

        unsigned int _glId;

    protected:

        GLObject();
        GLObject(const GLObject&) = delete;
        GLObject(GLObject&& glObject) noexcept;
        virtual ~GLObject();
    
        void setGLObjectId(unsigned int id);
        void unsetGLObjectId();

        virtual void createGLObject() = 0;
        virtual void destroyGLObject() = 0;
        virtual void resetGLObject();

    public:

        unsigned int getGLObjectId() const;
        virtual bool isValidGLObject() const;
    };
}

#endif
