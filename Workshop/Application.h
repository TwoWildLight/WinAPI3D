#pragma once
#include <core/Window.h>
#include <utility/Timer.h>
#include <rendering/IndexedTriangleList.h>
#include <rendering/Rasterizer.h>
#include <utility/Matrix.h>

class Application : public Window
{
private:
	Timer timer;

	Rasterizer rasterizer;
	IndexedTriangleList cube;
	Vector3 ang;

public:
	Application();
	~Application() = default;

	void Initiate();

private:
	void Update(float fDeltaTime);
	void Render(float fDeltaTime);
};