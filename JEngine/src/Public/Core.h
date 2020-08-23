// CORE ENGINE BEHAVIOR DEPENDS ON PLATFORMS
// CORE MACROS USED ALLOVER THE ENGINE
#pragma once

// DLL EXPORT/IMPORT ON DIFFERENT PLATFORMS
#ifdef JE_PLATFORM_WINDOWS
	#ifdef JE_BUILD_DLL
		#define JE_API __declspec(dllexport)
	#else
		#define JE_API __declspec(dllimport)
	#endif
#else
	#error JENGINE only support Windows 64-bit for now
#endif

// ASSERTION
#ifdef JE_ENABLE_ASSERTS
	#ifdef JE_PLATFORM_WINDOWS
		#define JE_ASSERT(x,...) {if (!(x)) { JE_ERROR("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); } }
		#define JE_CORE_ASSERT(x,...) {if (!(x)) { JE_CORE_ERROR("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); } }
	#endif
#else
	#define JE_ASSERT(x,...)
	#define JE_CORE_ASSERT(x,...)
#endif

// BIT OPERATOR
#define BIT(x) (1 << x)