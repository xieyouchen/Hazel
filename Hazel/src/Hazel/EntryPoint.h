#pragma once

#ifdef HZ_PLATFORM_WINDOWS                                                                                          

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	int a = 10;
	HZ_WARN("Watch out, Var a = {0}!", a);
	HZ_CORE_INFO("Hello!");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif
