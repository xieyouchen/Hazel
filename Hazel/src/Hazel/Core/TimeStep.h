#pragma once

namespace Hazel {
	class TimeStep {
	public:
		TimeStep(float time) : m_Time(time) {}

		operator float() { return m_Time; }
	private:
		float m_Time;
	};
}