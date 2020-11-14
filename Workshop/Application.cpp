#include "Application.h"
#include <core/Keyboard.h>
#include <rendering/Cube.h>

Application::Application()
	:
	Window((wchar_t*)L"Workshop", 1280u, 720u),
	camera(GetGFX(), { 0.0f, 0.0f, 0.0f }),
	rasterizer(GetGFX())
{
	camera.SetType(Camera::Type::FREE_VIEW);
	camera.SetFOV(PI_F / 2.0f);
	cube = Cube::Generate(1.0f);
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
	if (Keyboard::KeyIsDown(VK_ESCAPE))
	{
		if (IsCursorEnabled())
			DisableCursor();
		else EnableCursor();
	}

	camera.Update(fDeltaTime);
}

void Application::Render(float fDeltaTime)
{
	IndexedTriangleList itList = cube;

	float xFactor, yFactor;
	xFactor = yFactor = 320.0f;

	for (auto& v : itList.vertices)
	{
		Vector4 svPos(v.pos.x, v.pos.y, v.pos.z, 1.0f);

		// proejction
		svPos *= camera.GetViewMatrix();
		svPos *= camera.GetProjectionMatrix();

		// depth devide
		svPos.x /= abs(svPos.w);
		svPos.y /= abs(svPos.w);
		svPos.z /= abs(svPos.w);

		// screen transformation
		svPos.x *= 640.0f;
		svPos.y *= -360.0f;
		svPos += { 640.0f, 360.0f, 0.0f };

		v.pos = { svPos.x, svPos.y, svPos.z };
	}

	for (size_t i = 0; i < itList.indices.size(); i += 3u)
	{
		rasterizer.DrawLine({ itList.vertices[itList.indices[i + 0]].pos }, { itList.vertices[itList.indices[i + 1]].pos }, { 255.0f, 0.0f, 83.0f });
		rasterizer.DrawLine({ itList.vertices[itList.indices[i + 1]].pos }, { itList.vertices[itList.indices[i + 2]].pos }, { 255.0f, 0.0f, 83.0f });
		rasterizer.DrawLine({ itList.vertices[itList.indices[i + 2]].pos }, { itList.vertices[itList.indices[i + 0]].pos }, { 255.0f, 0.0f, 83.0f });
	}
}