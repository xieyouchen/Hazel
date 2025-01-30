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
}

void Hazel::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_windowHandle); //交换缓冲
}
