#include <Hazel.h>
#include "imgui/imgui.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	// 输入轮询
	void OnUpdate() override {
		if (Hazel::Input::IsKeyPressed(HZ_KEY_A)) {
			HZ_TRACE("A is pressed(polling)");
		}
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("m_Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	// 事件系统
	void OnEvent(Hazel::Event& event) override { 
		//if (event.GetEventType() == Hazel::EventType::KeyPressed) {
		//	Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
		//	auto keycode = e.GetKeyCode();
		//	if (keycode == HZ_KEY_A) {
		//		HZ_TRACE("A is pressed(event)");
		//	}
		//	HZ_TRACE("{0}", (char)keycode);
		//}
	}

};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer()); // 就是一直打印 ExampleLayer::Update，如果不想要了就注释
		// 要注意粉色窗口是 WindowsWindow::Init() 创建的
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}