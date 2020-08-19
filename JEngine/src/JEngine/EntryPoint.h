//This is the entry point of the Engine

#pragma once

#ifdef JE_PLATFORM_WINDOWS
extern JEngine::Application* JEngine::CreateApplication();

int main(int argc, char** argv) {
	auto app = JEngine::CreateApplication();
	app->Run();
	delete app;
}
#else
	#error JENGINE only support Windows 64-bit for now
#endif
