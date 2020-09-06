#pragma once

#include "RenderCommand.h"

namespace JEngine
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::RenderPlatform GetRenderPlatform() { return RendererAPI::GetRenderPlatform(); }
	};


}