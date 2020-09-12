#pragma once

#include "RenderCommand.h"

#include "Camera/OrthographicCamera.h"
#include "Renderer/Shader.h"

namespace JEngine
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::RenderPlatform GetRenderPlatform() { return RendererAPI::GetRenderPlatform(); }
	private:
		struct SceneData 
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};


}