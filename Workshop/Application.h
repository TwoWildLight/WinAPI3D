#pragma once
#include <src/core/Window.h>
#include <src/utility/Timer.h>

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