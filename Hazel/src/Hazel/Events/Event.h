#pragma once

//#include "Hazel/Core.h"

// 这两个都是C++标准库的文件，应该在预编译头文件中，或者包含在 Core.h 文件中

#include <string>
#include <functional>

namespace Hazel {
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0)
	};

}