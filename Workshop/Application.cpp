#include "Application.h"
#include <core/Keyboard.h>
#include <rendering/Cube.h>
#include <utility/CommonOps.h>

Application::Application()
	:
	Window((wchar_t*)L"Workshop", 1280u, 720u),
	rasterizer(GetGFX())
{
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
	if (Keyboard::KeyIsHold('A')) ang.y += fDeltaTime;
	if (Keyboard::KeyIsHold('D')) ang.y -= fDeltaTime;
	if (Keyboard::KeyIsHold('W')) ang.x += fDeltaTime;
	if (Keyboard::KeyIsHold('S')) ang.x -= fDeltaTime;

}

void Application::Render(float fDeltaTime)
{
	IndexedTriangleList itList = cube;
	Matrix mRotation = Matrix::Rotation(ang);

	float xFactor, yFactor;
	xFactor = yFactor = 320.0f;

	for (auto& v : itList.vertices)
	{
		v.pos *= mRotation;
		v.pos += { 0.0f, 0.0f, 3.0f };

		float zInv = 1.0f / v.pos.z;
		v.pos.x *= zInv;
		v.pos.y *= -zInv;

		v.pos *= 320.0f;
		v.pos += { 640.0f, 320.0f, 0.0f };
	}

	for (size_t i = 0; i < itList.indices.size(); i += 3u)
	{
		rasterizer.DrawLine({ itList.vertices[itList.indices[i + 0]].pos }, { itList.vertices[itList.indices[i + 1]].pos }, { 255.0f, 0.0f, 83.0f });
		rasterizer.DrawLine({ itList.vertices[itList.indices[i + 1]].pos }, { itList.vertices[itList.indices[i + 2]].pos }, { 255.0f, 0.0f, 83.0f });
		rasterizer.DrawLine({ itList.vertices[itList.indices[i + 2]].pos }, { itList.vertices[itList.indices[i + 0]].pos }, { 255.0f, 0.0f, 83.0f });
	}
}