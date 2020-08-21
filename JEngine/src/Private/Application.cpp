#include "JE_PCH.h"
#include "Application.h"
#include "Events/Event.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace JEngine {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280,720);
		JE_TRACE(e);
		while (true);
	}
}