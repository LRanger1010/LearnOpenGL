#pragma once
#include "Window.h"
#include "Renderer.h"
#include "tests/TestMenu.h"
#include "camera/Camera.h"

class WindowsWindow : public Window
{
public:
	WindowsWindow(const WindowProp& prop);
	~WindowsWindow();

	inline unsigned int GetWidth() override { return m_Data.Width; }
	inline unsigned int GetHeight() override { return m_Data.Height; }
	void OnUpdate() override;
	void SetVSync(bool enabled) override;
	bool IsVSync() override;

private:
	GLFWwindow* m_Window;
	WindowProp m_Data;
	bool m_VSyncEnabled;
	std::unique_ptr<Renderer> m_Renderer;
	std::unique_ptr<test::TestMenu> m_TestMenu;
	std::unique_ptr<CameraController> m_CameraController;
	float m_ClearColor[4];

	void Init();
	void Shutdown();
	void InitTest();
	void InitImGui();
};