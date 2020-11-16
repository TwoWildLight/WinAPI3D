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

	class TexturePixelShader : public PixelShader
	{
	public:
		virtual Vector4 operator()(PNTVertex& v) override
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