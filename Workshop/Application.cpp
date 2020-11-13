#include "Application.h"
#include <core/Mouse.h>

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
	for (int i = 0; i < 1280; i++)
	{
		GetGFX().PutPixel(i, 400, { 255.0f, 0.0f, 83.0f });
	}
}

void Application::Render(float fDeltaTime)
{
	bool debug = true;
}