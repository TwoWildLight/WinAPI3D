#pragma once
#include <chrono>

class Timer
{
private:
	std::chrono::steady_clock::time_point previous;

public:
	Timer() { previous = std::chrono::steady_clock::now(); }

	float Mark()
	{
		auto present = std::chrono::steady_clock::now();
		float elapsed = std::chrono::duration<float>(present - previous).count();
		previous = present;
		return elapsed;
	}

	float Peek() const
	{
		auto present = std::chrono::steady_clock::now();
		return std::chrono::duration<float>(present - previous).count();
	}
};