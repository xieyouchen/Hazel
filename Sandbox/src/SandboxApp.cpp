#include <Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override {
		HZ_INFO("ExampleLayer::Update"); // 最终会被输出
	}

	void OnEvent(Hazel::Event& e) override {
		// 似乎没有被输出？
		HZ_ERROR("Output!");
		HZ_TRACE("{0}", e); // 最终会被输出
	}

};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer()); // 就是一直打印 ExampleLayer::Update，如果不想要了就注释
		// 要注意粉色窗口是 WindowsWindow::Init() 创建的
		PushOverlay(new Hazel::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}