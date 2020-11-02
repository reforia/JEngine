#include "JE_PCH.h"
#include "Camera/OrthographicCameraController.h"

#include "Input.h"
#include "KeyCodes.h"

namespace JEngine
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep DeltaTime)
	{

		if (JEngine::Input::IsKeyDown(JE_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * DeltaTime;
		else if (JEngine::Input::IsKeyDown(JE_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * DeltaTime;

		if (JEngine::Input::IsKeyDown(JE_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * DeltaTime;
		else if (JEngine::Input::IsKeyDown(JE_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * DeltaTime;

		if (m_Rotation)
		{
			if (JEngine::Input::IsKeyDown(JE_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * DeltaTime;
			else if (JEngine::Input::IsKeyDown(JE_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * DeltaTime;
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
		m_Camera.SetRotation(m_CameraRotation);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.DispatchEvent<MouseScrollEvent>(EVENT_BIND_FUNCTION(OrthographicCameraController::OnMouseScrolled));
		dispatcher.DispatchEvent<WindowResizeEvent>(EVENT_BIND_FUNCTION(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrollEvent& e)
	{
		m_ZoomLevel -= e.GetMouseYOffset();
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWindowWidth() / (float)e.GetWindowHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}