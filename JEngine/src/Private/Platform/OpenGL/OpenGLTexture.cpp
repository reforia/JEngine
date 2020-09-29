#include "JE_PCH.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "glad/glad.h"
#include "stb_image.h"

namespace JEngine {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& texturePath)
		:m_TexturePath(texturePath)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
		JE_CORE_ASSERT(data, "Failed to load image at {0}, does it exist?", texturePath.c_str());
		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(const uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}