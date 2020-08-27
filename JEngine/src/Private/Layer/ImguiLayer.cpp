#include "JE_PCH.h"
#include "Layer/ImguiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImguiOpenGL.h"

#include "Application.h"
#include "Events/Event.h"

#include "GLFW/glfw3.h"
#include "KeyCodes.h"
#include "glad/glad.h"

namespace JEngine
{
	ImguiLayer::ImguiLayer()
		:Layer("ImguiLayer")
	{

	}

	ImguiLayer::~ImguiLayer()
	{

	}

	void ImguiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMP
		io.KeyMap[ImGuiKey_Tab] = JE_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = JE_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = JE_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = JE_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = JE_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = JE_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = JE_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = JE_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = JE_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = JE_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = JE_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = JE_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = JE_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = JE_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = JE_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = JE_KEY_A;
		io.KeyMap[ImGuiKey_C] = JE_KEY_C;
		io.KeyMap[ImGuiKey_V] = JE_KEY_V;
		io.KeyMap[ImGuiKey_X] = JE_KEY_X;
		io.KeyMap[ImGuiKey_Y] = JE_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = JE_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImguiLayer::OnDetach()
	{

	}

	void ImguiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWindowWidth(), app.GetWindow().GetWindowHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		// I think it will be better to have a switch to save some jump back
		dispatcher.DispatchEvent<MouseButtonPressedEvent>(EVENT_BIND_FUNCTION(ImguiLayer::OnMouseButtonPressedEvent));
		dispatcher.DispatchEvent<MouseButtonReleasedEvent>(EVENT_BIND_FUNCTION(ImguiLayer::OnMouseButtonReleasedEvent));
		dispatcher.DispatchEvent<MouseMoveEvent>(EVENT_BIND_FUNCTION(ImguiLayer::OnMouseMoveEvent));
		dispatcher.DispatchEvent<MouseScrollEvent>(EVENT_BIND_FUNCTION(ImguiLayer::OnMouseScrollEvent));
		dispatcher.DispatchEvent<KeyPressedEvent>(EVENT_BIND_FUNCTION(ImguiLayer::OnKeyPressedEvent));
		dispatcher.DispatchEvent<KeyReleasedEvent>(EVENT_BIND_FUNCTION(ImguiLayer::OnKeyReleasedEvent));
		dispatcher.DispatchEvent<KeyTypeEvent>(EVENT_BIND_FUNCTION(ImguiLayer::OnKeyTypeEvent));
		dispatcher.DispatchEvent<WindowResizeEvent>(EVENT_BIND_FUNCTION(ImguiLayer::OnWindowResizeEvent));
	}

	bool ImguiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		// Let other layers to respond this input event.
		return false;
	}

	bool ImguiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		// Let other layers to respond this input event.
		return false;
	}

	bool ImguiLayer::OnMouseMoveEvent(MouseMoveEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		// Let other layers to respond this input event.
		return false;
	}

	bool ImguiLayer::OnMouseScrollEvent(MouseScrollEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetMouseXOffset();
		io.MouseWheel += e.GetMouseYOffset();

		// Let other layers to respond this input event.
		return false;
	}

	bool ImguiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[JE_KEY_LEFT_CONTROL] || io.KeysDown[JE_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[JE_KEY_LEFT_SHIFT] || io.KeysDown[JE_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[JE_KEY_LEFT_ALT] || io.KeysDown[JE_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[JE_KEY_LEFT_SUPER] || io.KeysDown[JE_KEY_RIGHT_SUPER];

		// Let other layers to respond this input event.
		return false;
	}

	bool ImguiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		// Let other layers to respond this input event.
		return false;
	}

	bool ImguiLayer::OnKeyTypeEvent(KeyTypeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool ImguiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWindowWidth(), e.GetWindowHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		// TEMP
		glViewport(0, 0, e.GetWindowWidth(), e.GetWindowHeight());

		// Let other layers to respond this input event.
		return false;
	}

}

