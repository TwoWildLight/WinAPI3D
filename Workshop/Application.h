#pragma once
#include <core/Window.h>
#include <utility/Timer.h>
#include <components/Camera.h>
#include <utility/FPSCounter.h>
#include <utility/Pulsar.h>

class Application : public Window
{
private:
	Timer timer;
	Camera camera;
	FPSCounter fpsCounter;
	Pulsar fpsPulsar;

	DefaultVertexShader defaultVS;
	DefaultPixelShader defaultPS;

	class TexturePixelShader : public PixelShader
	{
	public:
		virtual Vector4 operator()(Vertex& v) override
		{
			return Sampler::Sample(v.tc, textures[0]);
		}
	}texturePS;

	std::unique_ptr<IndexedTriangleList> pCube0;
	std::unique_ptr<IndexedTriangleList> pCube1;

	std::unique_ptr<Texture> pTexture;

public:
	Application();
	~Application() = default;

	void Initiate();

private:
	void Update(float fDeltaTime);
	void Render(float fDeltaTime);
};