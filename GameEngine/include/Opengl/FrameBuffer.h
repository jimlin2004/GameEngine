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
        RED_INTEGER,

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
        FrameBufferTextureFormat textureFormat = FrameBufferTextureFormat::None;

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
        uint32_t samples = 0;
    };

    class FrameBuffer
    {
    private:
        FrameBufferSpecification specification;
        uint32_t rendererID;
        uint32_t depthAttachment;
        std::vector<FrameBufferTextureSpecification> colorAttachmentSpecifications;
        FrameBufferTextureSpecification depthAttachmentSpecification;
        std::vector<uint32_t> colorAttachments;
    public:
        FrameBuffer();
        FrameBuffer(const FrameBufferSpecification& spec);
        virtual ~FrameBuffer();
        void generate();
        void resize(uint32_t width, uint32_t height);
        void bind();
        void unbind();
        int readPixel(uint32_t attachmentIndex, int x, int y);
        void clearAttachment(uint32_t attachmentIndex, int initValue);

        inline uint32_t getColorAttachmentRendererID(uint32_t index = 0) const
        {
            assert(index < this->colorAttachments.size());
            return this->colorAttachments[index];
        }
        inline uint32_t getDepthAttachmentRendererID() const
        {
            return this->depthAttachment;
        }
    };
}

#endif