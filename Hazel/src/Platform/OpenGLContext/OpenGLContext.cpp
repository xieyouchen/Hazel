#include "hzpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Hazel::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_windowHandle(windowHandle)
{

}

void Hazel::OpenGLContext::Init()
{
	// 设置 glfw 的上下文
	glfwMakeContextCurrent(m_windowHandle);

	// 在运行时候获取 OpenGL 函数地址并保存到函数指针
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HZ_CORE_ASSERT(status, "初始化Glad失败.");

	HZ_CORE_INFO("OpenGL info:");
	HZ_CORE_INFO("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));//打印厂商
	HZ_CORE_INFO("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
	HZ_CORE_INFO("	Version: {0}",(const char*)glGetString(GL_VERSION));
}

void Hazel::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_windowHandle); //交换缓冲
}
