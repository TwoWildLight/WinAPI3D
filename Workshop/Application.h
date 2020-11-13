#pragma once
#include <core/Window.h>
#include <utility/Timer.h>

class Application : public Window
{
private:
	Timer timer;

public:
	Application();
	~Application() = default;

	void Initiate();

private:
	void Update(float fDeltaTime);
	void Render(float fDeltaTime);
};