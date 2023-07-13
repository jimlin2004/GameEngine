#include "Opengl/FrameBuffer.h"

GameEngine::FrameBuffer::FrameBuffer()
{
}

GameEngine::FrameBuffer::FrameBuffer(uint32_t width, uint32_t height)
    : width(width)
    , height(height)
    , rendererID(0U)
    , colorAttachment(0U)
    , depthAttachment(0U)
{
    this->generate();
}

GameEngine::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &this->rendererID);
    glDeleteTextures(1, &this->colorAttachment);
    glDeleteRenderbuffers(1, &this->depthAttachment);
}

void GameEngine::FrameBuffer::generate()
{
    if (this->rendererID)
    {
        glDeleteFramebuffers(1, &this->rendererID);
        glDeleteTextures(1, &this->colorAttachment);
        glDeleteRenderbuffers(1, &this->depthAttachment);
    }
    glCreateFramebuffers(1, &this->rendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, this->rendererID);

    glGenTextures(1, &this->colorAttachment);
    glBindTexture(GL_TEXTURE_2D, this->colorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorAttachment, 0);

    // glCreateTextures(GL_TEXTURE_2D, 1, &this->depthAttachment);
    // glBindTexture(GL_TEXTURE_2D, this->depthAttachment);
    // glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, this->width, this->height);
    // // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->width, this->height, 0,
    // 	// GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->depthAttachment, 0);
    glGenRenderbuffers(1, &this->depthAttachment);
    glBindRenderbuffer(GL_RENDERBUFFER, this->depthAttachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->depthAttachment);

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void GameEngine::FrameBuffer::resize(uint32_t width, uint32_t height)
{
    this->width = width;
    this->height = height;
    this->generate();
}
void GameEngine::FrameBuffer::bind()
{
    glViewport(0, 0, this->width, this->height);
    glBindFramebuffer(GL_FRAMEBUFFER, this->rendererID);
}

void GameEngine::FrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
uint32_t GameEngine::FrameBuffer::getColorAttachmentRendererID() const
{
    return this->colorAttachment;
}
