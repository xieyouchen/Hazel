#include <Hazel.h>
#include "imgui/imgui.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-2, 2, -2, 2)
	{
		m_VertexArray.reset(Hazel::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,	-0.5f,	0.0f,   0.8f, 0.2f, 0.2f, 1.0f,
			0.5f,	-0.5f,	0.0f,	0.2f, 0.2f, 0.8f, 1.0f,
			0.0f,	0.5f,	0.0f,	0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<Hazel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		Hazel::BufferLayout layout = {
			{Hazel::ShaderDataType::Float3, "a_Position"},
			{Hazel::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				v_Color = a_Color;
				v_Position = a_Position;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader.reset(new Hazel::Shader(vertexSrc, fragmentSrc));


		m_SquareVAO.reset(Hazel::VertexArray::Create());
		float squareVertices[4 * 3] = {
			-0.75f,	-0.75f,	0.0f,
			 0.75f,	-0.75f,	0.0f,
			 0.75f,	 0.75f,	0.0,
			-0.75f,	 0.75f,	0.0,
		};
		std::shared_ptr<Hazel::VertexBuffer> SquareBuffer;
		SquareBuffer.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Hazel::BufferLayout squareLayout = {
			{Hazel::ShaderDataType::Float3, "a_Position"},
		};
		SquareBuffer->SetLayout(squareLayout);
		m_SquareVAO->AddVertexBuffer(SquareBuffer);

		unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Hazel::IndexBuffer> SquareIndexBuffer;
		SquareIndexBuffer.reset(Hazel::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(SquareIndexBuffer);

		std::string SquareVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main() {
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				v_Position = a_Position;
			}
		)";

		std::string SquareFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			void main() {
				color = vec4(0.6f, 0.6f, 0.6f, 1.0f);
			}
		)";
		m_BlueShader.reset(new Hazel::Shader(SquareVertexSrc, SquareFragmentSrc));
	}

	// 输入轮询
	void OnUpdate() override {
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f,0.1f, 1 });
		Hazel::RenderCommand::Clear();

		//m_Camera.SetPosition({ 0.5, 0.5, 0 });
		m_Camera.SetRotation(45.0f);

		Hazel::Renderer::BeginScene(m_Camera);

		Hazel::Renderer::Submit(m_BlueShader, m_SquareVAO);

		Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		Hazel::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

	}

	// 事件系统
	void OnEvent(Hazel::Event& event) override { 

	}

private:
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;
	std::shared_ptr<Hazel::Shader> m_Shader;

	std::shared_ptr<Hazel::VertexArray> m_SquareVAO;
	std::shared_ptr<Hazel::Shader> m_BlueShader;

	Hazel::OrthographicCamera m_Camera;

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