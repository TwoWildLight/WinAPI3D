#pragma once
#include <core/Window.h>
#include <utility/Timer.h>
#include <components/Camera.h>

class Application : public Window
{
private:
	Timer timer;
	Camera camera;

	VertexShader defaultVS;
	PixelShader defaultPS;

	std::unique_ptr<IndexedTriangleList> pCube;

public:
	Application();
	~Application() = default;

	void Initiate();

private:
	void Update(float fDeltaTime);
	void Render(float fDeltaTime);
};