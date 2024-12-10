#pragma once
#include "Hazel/Input.h"

namespace Hazel {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
	};
}