#include "Opengl/FrameBuffer.h"

GameEngine::FrameBuffer::FrameBuffer()
{
}

GameEngine::FrameBuffer::FrameBuffer(uint32_t width, uint32_t height)
    : width(width)
    , height(height)
{
}

GameEngine::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &this->rendererID);
}

void GameEngine::FrameBuffer::resize()
{
    glCreateFramebuffers(1, &this->rendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, this->rendererID);
    
    glCreateTextures(GL_TEXTURE_2D, 1, &this->colorAttachment);
    glBindTexture(GL_TEXTURE_2D, this->colorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorAttachment, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &this->depthAttachment);
    glBindTexture(GL_TEXTURE_2D, this->depthAttachment);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, this->width, this->height);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->width, this->height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->depthAttachment, 0);

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void GameEngine::FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->rendererID);
}

void GameEngine::FrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
uint32_t GameEngine::FrameBuffer::gettColorAttachmentRendererID() const
{
    return this->colorAttachment;
}
