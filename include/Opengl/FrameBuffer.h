#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <stdint.h>
#include "GL/glew.h"
#include <assert.h>

namespace GameEngine
{
    class FrameBuffer
    {
    private:
        uint32_t width;
        uint32_t height;
        uint32_t rendererID;
        uint32_t colorAttachment;
        uint32_t depthAttachment;
    public:
        FrameBuffer();
        FrameBuffer(uint32_t width, uint32_t height);
        virtual ~FrameBuffer();
        void resize();
        void bind();
        void unbind();
        uint32_t gettColorAttachmentRendererID() const;
    };
}

#endif