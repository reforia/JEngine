#include "JE_PCH.h"
#include "Renderer/Shader.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace JEngine
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetRenderPlatform())
		{
		case RendererAPI::RenderPlatform::None: JE_CORE_ASSERT(false, "RendererAPI::None is not suppported!"); return nullptr;
		case RendererAPI::RenderPlatform::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}

		JE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetRenderPlatform())
		{
		case RendererAPI::RenderPlatform::None: JE_CORE_ASSERT(false, "RendererAPI::None is not suppported!"); return nullptr;
		case RendererAPI::RenderPlatform::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		JE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader.GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		JE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}


	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		JE_CORE_ASSERT(Exists(name), "Shader Not Found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}