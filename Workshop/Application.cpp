#include "Application.h"
#include <core/Keyboard.h>
#include <rendering/Cube.h>
#include <rendering/TransformCBuf.h>

Application::Application()
	:
	Window((wchar_t*)L"Workshop", 1280u, 720u),
	camera(GetGFX(), { 0.0f, 0.0f, -3.0f })
{
	DisableCursor();

	camera.SetType(Camera::Type::FREE_VIEW);

	GetGFX().SetTopology(Context::Topology::LINE_LIST);
	GetGFX().BindVertexShader(&defaultVS);
	GetGFX().BindPixelShader(&defaultPS);

	pCube = std::make_unique<IndexedTriangleList>(Cube::CreateCube(1.0f));
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

	TransformCBuf tcbuf;
	auto mView = camera.GetViewMatrix();
	auto mProj = camera.GetProjectionMatrix();
	tcbuf.SetViewMatrix(mView);
	tcbuf.SetViewProjectionMatrix(mView * mProj);
	defaultVS.SetTransformCBuf(tcbuf);
}

void Application::Render(float fDeltaTime)
{
	GetGFX().Render(*pCube);
}