// THE ENGINE CLASS IS DEFINED HERE
#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Layer/LayerStack.h"
#include "Layer/ImguiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

namespace JEngine {
	class JE_API Application 
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; };
		inline Window& GetWindow() { return *m_Window; };

	private:
		bool OnWindowCloseEvent(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImguiLayer* m_ImguiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;

		std::unique_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
	};

	Application* CreateApplication();

}