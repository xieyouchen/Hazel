#include "hzpch.h"

#include "Application.h"
#include "Log.h"
//#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Input.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Hazel::Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// 创建了一个窗口
		m_Window = std::unique_ptr<Window>(Window::Create());
		
		// 设置窗口事件的回调函数
		// param: std::function<void(Event&)>
		//m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		//m_Window->SetEventCallback(this->OnEvent);
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// 将 ImGuiLayer 放在最后
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		//glGenVertexArrays(1, &m_VertexArray);
		//glBindVertexArray(m_VertexArray);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,	-0.5f,	0.0f,   0.8f, 0.2f, 0.2f, 1.0f,
			0.5f,	-0.5f,	0.0f,	0.2f, 0.2f, 0.8f, 1.0f,
			0.0f,	0.5f,	0.0f,	0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				gl_Position = vec4(a_Position, 1.0);
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
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));


		m_SquareVAO.reset(VertexArray::Create());
		float squareVertices[4 * 3] = {
			-0.75f,	-0.75f,	0.0f,  
			 0.75f,	-0.75f,	0.0f,	
			 0.75f,	 0.75f,	0.0,
			-0.75f,	 0.75f,	0.0,
		};
		std::shared_ptr<VertexBuffer> SquareBuffer;
		SquareBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		BufferLayout squareLayout = {
			{ShaderDataType::Float3, "a_Position"},
		};
		SquareBuffer->SetLayout(squareLayout);
		m_SquareVAO->AddVertexBuffer(SquareBuffer);

		unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> SquareIndexBuffer;
		SquareIndexBuffer.reset(IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(SquareIndexBuffer);

		std::string SquareVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main() {
				gl_Position = vec4(a_Position, 1.0);
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
		m_BlueShader.reset(new Shader(SquareVertexSrc, SquareFragmentSrc));
	}

	Hazel::Application::~Application()
	{
	}	

	// ------ Layer
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e) 
	{
		//HZ_ERROR("Application OnEvent");
		// 通过事件调度器判断是否为窗口关闭事件
		EventDispatcher dispatcher(e);
		//dispatcher.Dispathcer<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispathcer<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.m_Handled) {
				break;
			}
		}
		
		//HZ_CORE_INFO("{0}", e); // 开头会带 Hazel，绿色字体
	}

	// 窗口关闭的回调函数
	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Hazel::Application::Run()
	{
		while (m_Running) {
			// run中使用了opengl函数
			glClearColor(0.1f, 0.1f,0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_BlueShader->Bind();
			m_SquareVAO->Bind();
			// 注意最后一个参数是 nullptr
			glDrawElements(GL_TRIANGLES, m_SquareVAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);


			m_Shader->Bind();
			m_VertexArray->Bind();
			// 注意最后一个参数是 nullptr
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			
			// 从前往后顺序更新层
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//m_ImGuiLayer->Begin();
			// //从前往后顺序更新层
			//for (Layer* layer : m_LayerStack)
			//	layer->OnImGuiRender();
			//m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}

