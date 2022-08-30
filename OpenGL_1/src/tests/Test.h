#pragma once

namespace test {
	class Test
	{
	public:
		Test() {}
		~Test() {}

		virtual void OnUpdate(float deltaTime){}
		virtual void OnRender(){}
		virtual void OnGUI(){ ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); }

	private:

	};
}