//This is the entry point of the Engine

#pragma once

#ifdef JE_PLATFORM_WINDOWS
extern JEngine::Application* JEngine::CreateApplication();

int main(int argc, char** argv) {
	JEngine::Log::Init();
	JE_CORE_WARN("Initialized Log!");
	int a = 5;
	JE_INFO("Hello! var = {0}",a);


	auto app = JEngine::CreateApplication();
	app->Run();
	delete app;
}
#else
	#error JENGINE only support Windows 64-bit for now
#endif
