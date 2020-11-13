#pragma once
#include "LightWindows.h"

class Graphics final
{
private:
	HDC hDC;

	UINT screenWidth;
	UINT screenHeight;
	bool bFullscreen;

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
};