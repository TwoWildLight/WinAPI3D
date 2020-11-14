#pragma once
#include <core/Window.h>
#include <utility/Timer.h>
#include <rendering/IndexedTriangleList.h>
#include <rendering/Rasterizer.h>
#include <components/Camera.h>

class Application : public Window
{
private:
	Timer timer;
	Camera camera;

	Rasterizer rasterizer;
	IndexedTriangleList cube;

public:
	Application();
	~Application() = default;

	void Initiate();

private:
	void Update(float fDeltaTime);
	void Render(float fDeltaTime);
};