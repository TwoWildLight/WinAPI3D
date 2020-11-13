#include "Graphics.h"

Graphics::Graphics(HWND hWnd, UINT w, UINT h)
	:
	screenWidth(w),
	screenHeight(h)
{
	hDC = GetDC(hWnd);
}

void Graphics::BeginFrame()
{
	Rectangle(hDC, 100, 100, 300, 300);
}

void Graphics::EndFrame()
{

}

UINT Graphics::GetWidth() const
{
	return screenWidth;
}

UINT Graphics::GetHeight() const
{
	return screenHeight;
}

bool Graphics::IsFullScreen() const
{
	return bFullscreen;
}