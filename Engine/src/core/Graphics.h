#pragma once
#include "LightWindows.h"
#include "../rendering/Texture.h"

class Graphics final
{
private:
	HDC hMainDC;
	HDC hBufferDC;

	std::unique_ptr<Texture> pRenderTargetView;

	UINT screenWidth;
	UINT screenHeight;

	UINT resolutionWidth;
	UINT resolutionHeight;

	const float resolutionScale = 1.0f;

public:
	Graphics(HWND hWnd, UINT w, UINT h);
	~Graphics() = default;

	Graphics(const Graphics&) = delete;
	Graphics(Graphics&&) = delete;
	Graphics& operator =(const Graphics&) = delete;

public:
	void BeginFrame();
	void EndFrame();

	UINT GetWidth() const;
	UINT GetHeight() const;

	void PutPixel(UINT x, UINT y, const Vector3& c);
};