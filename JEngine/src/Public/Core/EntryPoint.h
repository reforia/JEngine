//CORE ENGINE ENTRY POINT
#pragma once

#ifdef JE_PLATFORM_WINDOWS
extern JEngine::Application* JEngine::CreateApplication();

int main(int argc, char** argv) {

	JEngine::Log::Init();
	JE_CORE_WARN("Initialized Log!");

	// Let the actual project to implement the CreateApplication() and return the app*
	auto app = JEngine::CreateApplication();

	// Run the app just created
	app->Run();

	// While the app finished running, release the memory
	// Call ~(), and don't necessarily need to free the pointer as it will be destroyed
	// when main() returns anyway.
	delete app;
}
#else
	#error JENGINE only support Windows 64-bit for now
#endif
