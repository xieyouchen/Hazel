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
	// ���� glfw ��������
	glfwMakeContextCurrent(m_windowHandle);

	// ������ʱ���ȡ OpenGL ������ַ�����浽����ָ��
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HZ_CORE_ASSERT(status, "��ʼ��Gladʧ��.");
}

void Hazel::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_windowHandle); //��������
}
