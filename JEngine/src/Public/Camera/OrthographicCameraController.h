#pragma once

#include "../Camera/OrthographicCamera.h"
#include "../Core/Timestep.h"

#include "../Events/ApplicationEvent.h"
#include "../Events/MouseEvent.h"
#include "glm/glm.hpp"

namespace JEngine
{

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep DeltaTime);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrollEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera; // make sure this is initialized later

		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		float m_CameraTranslationSpeed = 2.0f;
		float m_CameraRotationSpeed = 1.0f;
	};
}