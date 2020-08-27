#include "JE_PCH.h"
#include "Application.h"
#include "Events/Event.h"
#include "glad/glad.h"
#include "Input.h"
#include "Layer/ImguiLayer.h"

namespace JEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		JE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Create default JEngine Editor Window
		m_Window = std::unique_ptr<Window>(Window::CreateJEWindow());
		m_Window->SetEventCallback(EVENT_BIND_FUNCTION(Application::OnEvent));

		m_ImguiLayer = new ImguiLayer();
		PushOverlay(m_ImguiLayer);
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.DispatchEvent<WindowCloseEvent>(EVENT_BIND_FUNCTION(Application::OnWindowCloseEvent));
		// JE_CORE_INFO("{0}", e);

		// Back trace layer to get the response layer
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*(--it))->OnEvent(e);
			if (e.m_handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	Application::~Application() {

	}

	void Application::Run() {
		//WindowResizeEvent e(1280,720);
		//JE_TRACE(e);
		while (m_Running) {
			// Clear Buffer
			glClearColor(0.3, 0.3, 0.3, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Update Objects Based on layer order
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			m_ImguiLayer->begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImguiRender();
			}
			m_ImguiLayer->end();

			// With input Polling, we can do things like:
			// JE_CORE_TRACE("Is Key K pressed? {0}", Input::IsKeyDown(75));
			
			// Render Logic
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}