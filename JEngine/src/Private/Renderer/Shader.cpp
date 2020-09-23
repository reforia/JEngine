#include "JE_PCH.h"
#include "Renderer/Shader.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace JEngine
{

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetRenderPlatform())
		{
		case RendererAPI::RenderPlatform::None: JE_CORE_ASSERT(false, "RendererAPI::None is not suppported!"); return nullptr;
		case RendererAPI::RenderPlatform::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		JE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

}