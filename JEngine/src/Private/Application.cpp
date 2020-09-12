#include "JE_PCH.h"
#include "Application.h"
#include "Events/Event.h"
#include "Renderer/Renderer.h"
#include "Input.h"
#include "Layer/ImguiLayer.h"
#include "Renderer/Buffer.h"


namespace JEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application() 
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		JE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Create default JEngine Editor Window
		m_Window = std::unique_ptr<Window>(Window::CreateJEWindow());
		m_Window->SetEventCallback(EVENT_BIND_FUNCTION(Application::OnEvent));

		m_ImguiLayer = new ImguiLayer();
		PushOverlay(m_ImguiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.5f, 0.4f, 0.1f, 1.0f,
			0.5, -0.5f, 0.0f, 0.1f, 0.4f, 0.5f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.2f, 0.1f, 0.4f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;	
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(v_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

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
			RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
			RenderCommand::Clear();

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_Shader, m_VertexArray);

			Renderer::EndScene();

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