#include "Application.h"

Application::Application()
	:
	Window((wchar_t*)L"Workshop", 1280u, 720u)
{
}

void Application::Initiate()
{
	while (ProceedMessage())
	{
		GetGFX().BeginFrame();
		Update(timer.Mark());
		Render(timer.Peek());
		GetGFX().EndFrame();
	}
}

void Application::Update(float fDeltaTime)
{
}

void Application::Render(float fDeltaTime)
{
}