#include "Opengl/FrameBuffer.h"

GameEngine::FrameBuffer::FrameBuffer()
{
}

static bool isDepthFormat(GameEngine::FrameBufferTextureFormat format)
{
    switch (format)
    {
    case GameEngine::FrameBufferTextureFormat::DEPTH24_STENCIL8 :
        return true;
    
    default:
        return false;
    }
}

static GLenum textureTarget(bool multisampled)
{
    return (multisampled) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

static void attachColorTexture(uint32_t id, uint32_t samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, size_t index)
{
    bool multisampled = (samples > 1);
    if (multisampled)
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, textureTarget(multisampled), id, 0);
}

static void attachDepthTexture(uint32_t id, uint32_t samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
{
    bool multisampled = (samples > 1);
    if (multisampled)
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
    else
    {
        glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, textureTarget(multisampled), id, 0);
}

static void createTextures(bool multisampled, uint32_t* outID, uint32_t count)
{
    glCreateTextures(textureTarget(multisampled), count, outID);
}

static void bindTexture(bool multisampled, uint32_t id)
{
    glBindTexture(textureTarget(multisampled), id);
}

static GLenum textureFormatToGLenum(GameEngine::FrameBufferTextureFormat format)
{
    switch (format)
    {
    case GameEngine::FrameBufferTextureFormat::RGBA8: return GL_RGBA8;
    case GameEngine::FrameBufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
    default:
        break;
    }
    assert(false);
    return 0;
}

GameEngine::FrameBuffer::FrameBuffer(const FrameBufferSpecification& spec)
    : specification(spec)
    , rendererID(0U)
    , depthAttachment(0U)
{
    for (GameEngine::FrameBufferTextureSpecification spec: this->specification.attachments.attachments)
    {
        if (!isDepthFormat(spec.textureFormat))
            this->colorAttachmentSpecifications.emplace_back(spec);
        else
            this->depthAttachmentSpecification = spec;
    }

    this->generate();
}

GameEngine::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &this->rendererID);
    glDeleteTextures(this->colorAttachments.size(), this->colorAttachments.data());
    glDeleteTextures(1, &this->depthAttachment);
}

void GameEngine::FrameBuffer::generate()
{
    if (this->rendererID)
    {
        glDeleteFramebuffers(1, &this->rendererID);
        glDeleteTextures(this->colorAttachments.size(), this->colorAttachments.data());
        glDeleteTextures(1, &this->depthAttachment);
        this->colorAttachments.clear();
        this->depthAttachment = 0;
    }
    glCreateFramebuffers(1, &this->rendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, this->rendererID);

    bool multisampled = (this->specification.samples > 1);

    if (this->colorAttachmentSpecifications.size())
    {
        this->colorAttachments.resize(this->colorAttachmentSpecifications.size());
        createTextures(multisampled, this->colorAttachments.data(), this->colorAttachments.size());
        for (size_t i = 0; i < this->colorAttachments.size(); ++i)
        {
            bindTexture(multisampled, this->colorAttachments[i]);
            switch (this->colorAttachmentSpecifications[i].textureFormat)
            {
            case GameEngine::FrameBufferTextureFormat::RGBA8:
                attachColorTexture(this->colorAttachments[i], this->specification.samples, GL_RGB8, GL_RGBA, this->specification.width, this->specification.height, i);
                break;
            case GameEngine::FrameBufferTextureFormat::RED_INTEGER:
                attachColorTexture(this->colorAttachments[i], this->specification.samples, GL_R32I, GL_RED_INTEGER, this->specification.width, this->specification.height, i);
                break;
            default:
                break;
            }
        }
    }

    if (this->depthAttachmentSpecification.textureFormat != GameEngine::FrameBufferTextureFormat::None)
    {
        createTextures(multisampled, &this->depthAttachment, 1);
        bindTexture(multisampled, this->depthAttachment);
        switch (this->depthAttachmentSpecification.textureFormat)
        {
        case GameEngine::FrameBufferTextureFormat::DEPTH24_STENCIL8 :
            attachDepthTexture(this->depthAttachment, this->specification.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, this->specification.width, this->specification.height);
            break;
        
        default:
            break;
        }
    }

    if (this->colorAttachments.size() > 1)
    {
        assert(this->colorAttachments.size() <= 4);
        static constexpr GLenum buffer[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
        glDrawBuffers(this->colorAttachments.size(), buffer);
    }
    else if (this->colorAttachments.empty())
    {
        //only depth
        glDrawBuffer(GL_NONE);
    }

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GameEngine::FrameBuffer::resize(uint32_t width, uint32_t height)
{
    this->specification.width = width;
    this->specification.height = height;
    this->generate();
}
void GameEngine::FrameBuffer::bind()
{
    glViewport(0, 0, this->specification.width, this->specification.height);
    glBindFramebuffer(GL_FRAMEBUFFER, this->rendererID);
}

void GameEngine::FrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int GameEngine::FrameBuffer::readPixel(uint32_t attachmentIndex, int x, int y)
{
    assert(attachmentIndex < this->colorAttachments.size());
    glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
    int pixelData;
    glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
    return pixelData;
}

void GameEngine::FrameBuffer::clearAttachment(uint32_t attachmentIndex, int initValue)
{
    assert(attachmentIndex < this->colorAttachments.size());

    GameEngine::FrameBufferTextureSpecification& spec = this->colorAttachmentSpecifications[attachmentIndex];
    glClearTexImage(this->colorAttachments[attachmentIndex], 0,
    textureFormatToGLenum(spec.textureFormat), GL_INT, &initValue);
    //glClearTexImage 似乎可以用glClearBufferiv代替(3.3可用)
}
