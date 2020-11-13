#pragma once
#include "LightWindows.h"
#include "../rendering/Texture.h"

class Graphics final
{
private:
	UINT screenWidth;
	UINT screenHeight;

	HDC hMainDC;
	Texture rendertarget;

	bool bFullScreen;

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
	bool IsFullScreen() const;

	void PutPixel(UINT x, UINT y, const Vector3& c);
};