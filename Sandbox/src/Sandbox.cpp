#include "JEngine.h"

class Sandbox : public JEngine::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

JEngine::Application* JEngine::CreateApplication() {
	return new Sandbox();
}