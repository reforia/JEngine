#include "JEngine.h"

class ExampleLayer : public JEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() override 
	{
		JE_INFO("Example Layer Updated!");
	}

	void OnEvent(JEngine::Event& e) override
	{
		JE_TRACE("{0}", e);
	}
};

class Sandbox : public JEngine::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new JEngine::ImguiLayer());
	}

	~Sandbox() {

	}
};

JEngine::Application* JEngine::CreateApplication() {
	return new Sandbox();
}