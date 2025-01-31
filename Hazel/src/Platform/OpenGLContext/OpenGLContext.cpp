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

	HZ_CORE_INFO("OpenGL info:");
	HZ_CORE_INFO("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));//��ӡ����
	HZ_CORE_INFO("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
	HZ_CORE_INFO("	Version: {0}",(const char*)glGetString(GL_VERSION));
}

void Hazel::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_windowHandle); //��������
}
