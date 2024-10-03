#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel {
	static bool s_GLFWInitialized = false;
	
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	static void GLFWErrorCallback(int error_code, const char* description) {
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		HZ_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!"); // Core.h 预处理器定义了HZ_CORE_ASSERT
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		// 创建窗口
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);

		// 设置 glfw 的上下文
		glfwMakeContextCurrent(m_Window);


		// 设置窗口关联的用户数据指针，m_Data& 会以 void* 的形式和 m_Window 绑定
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		
		// 执行glfw窗口事件，同时设置回调
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			// 获取和窗口关联的用户数据指针 void*，需要显式转化为用户数据指针(m_Data)自定义的数据类型(WindowData*)
			// 设置回调函数默认允许执行窗口事件
			// 此处逻辑用于回调，即使回调逻辑为空，窗口大小也可以自由改变
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			// 设置自定义的窗口事件数据类型
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS:{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
			}
		});
		
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});

		
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xpos, (float)ypos);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents(); // 轮询事件
		glfwSwapBuffers(m_Window); //交换缓冲
	}
}
