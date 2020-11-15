#pragma once
#include <core/Window.h>
#include <utility/Timer.h>
#include <components/Camera.h>

class Application : public Window
{
private:
	Timer timer;
	Camera camera;

	DefaultVertexShader defaultVS;
	DefaultPixelShader defaultPS;

	class FaceColorPixelShader : public PixelShader
	{
	public:
		virtual Vector4 operator()(PNVertex& v) override
		{
			return Vector4(abs(v.n.x), abs(v.n.y), abs(v.n.z), 1.0f);
		}
	}facePixelShader;

	std::unique_ptr<IndexedTriangleList> pCube0;
	std::unique_ptr<IndexedTriangleList> pCube1;

public:
	Application();
	~Application() = default;

	void Initiate();

private:
	void Update(float fDeltaTime);
	void Render(float fDeltaTime);
};