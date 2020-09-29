#pragma once

#include "Renderer/Texture.h"

namespace JEngine {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& texturePath);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(const uint32_t slot = 0) const override;

	private:
		std::string m_TexturePath; // Consider move this into an Asset Manager in the future
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};
}