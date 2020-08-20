#pragma once

#include "Core.h"

namespace JEngine {

	class JE_API Application {

	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}