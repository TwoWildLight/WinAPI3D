#pragma once
#include <core/Window.h>
#include <utility/Timer.h>
#include <components/Camera.h>
#include "rendering/VertexShader.h"

class Application : public Window
{
private:
	Timer timer;
	Camera camera;

	VertexShader defaultVS;

	std::unique_ptr<IndexedTriangleList> pCube;

public:
	Application();
	~Application() = default;

	void Initiate();

private:
	void Update(float fDeltaTime);
	void Render(float fDeltaTime);
};