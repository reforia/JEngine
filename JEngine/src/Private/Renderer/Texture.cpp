#include "JE_PCH.h"
#include "Renderer/Texture.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace JEngine {

	Ref<Texture2D> Texture2D::Create(const std::string& texturePath)
	{
		switch (Renderer::GetRenderPlatform())
		{
		case RendererAPI::RenderPlatform::None: JE_CORE_ASSERT(false, "RendererAPI::None is not suppported!"); return nullptr;
		case RendererAPI::RenderPlatform::OpenGL: return std::make_shared<OpenGLTexture2D>(texturePath);
		}

		JE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}

