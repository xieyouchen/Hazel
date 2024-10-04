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
		HZ_TRACE("{0}", e); // 最终会被输出
	}

};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}