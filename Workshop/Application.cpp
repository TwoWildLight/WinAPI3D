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

	GetGFX().SetTopology(Context::Topology::TRIANGLE_LIST);
	GetGFX().BindVertexShader(&defaultVS);
	pTexture = std::make_unique<Texture>("Images/BlueDice.png");

	texturePS.BindTexture(pTexture.get());
	GetGFX().BindPixelShader(&texturePS);

	pCube0 = std::make_unique<IndexedTriangleList>(Cube::CreateCube(1.0f));
	pCube0->GenerateIndividualFaceNormals();
	pCube1 = std::make_unique<IndexedTriangleList>(Cube::CreateCube(1.0f));
	pCube1->GenerateIndividualFaceNormals();

	float ang = PI_F / 4.0f;
	auto m = Matrix::Rotation({ ang, ang, ang });
	for (auto& v : pCube1->vertices)
	{
		v.pos *= m;
		v.n *= m;
	}
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
	GetGFX().Render(*pCube0);
	GetGFX().Render(*pCube1);
}