#pragma once

#include <string>
#include "glm/glm.hpp"

namespace JEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	private:
		uint32_t m_RendererID;
	};
}