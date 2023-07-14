#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <stdint.h>
#include "GL/glew.h"
#include <assert.h>
#include <vector>

namespace GameEngine
{
    enum class FrameBufferTextureFormat
    {
        None = 0,
        
        //color
        RGBA8,

        //depth/stencil
        DEPTH24_STENCIL8,

        //defaults
        Depth = DEPTH24_STENCIL8
    };

    struct FrameBufferTextureSpecification
    {
        FrameBufferTextureSpecification() = default;
        FrameBufferTextureSpecification(FrameBufferTextureFormat format)
            : textureFormat(format)
        {
        }
        FrameBufferTextureFormat textureFormat;

        // Todo: filtering/wrap
    };

    struct FrameBufferAttachmentSpecification
    {
        FrameBufferAttachmentSpecification() = default;
        FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachmentsList)
            : attachments(attachmentsList)
        {
        }
        std::vector<FrameBufferTextureSpecification> attachments;
    };

    struct FrameBufferSpecification
    {
        uint32_t width = 0, height = 0;
        FrameBufferAttachmentSpecification attachments;
    };

    class FrameBuffer
    {
    private:
        FrameBufferSpecification specification;
        uint32_t rendererID;
        uint32_t colorAttachment;
        uint32_t depthAttachment;
    public:
        FrameBuffer();
        FrameBuffer(const FrameBufferSpecification& spec);
        virtual ~FrameBuffer();
        void generate();
        void resize(uint32_t width, uint32_t height);
        void bind();
        void unbind();
        inline uint32_t getColorAttachmentRendererID() const
        {
            return this->colorAttachment;
        }
        inline uint32_t getDepthAttachmentRendererID() const
        {
            return this->depthAttachment;
        }
    };
}

#endif