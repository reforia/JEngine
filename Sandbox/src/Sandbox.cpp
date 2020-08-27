#include "JEngine.h"

#include "imgui/imgui.h"

class ExampleLayer : public JEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() override 
	{
		// JE_INFO("Example Layer Updated!");
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
	}

	~Sandbox() {

	}
};

JEngine::Application* JEngine::CreateApplication() {
	return new Sandbox();
}