#include "Graphics.h"

Graphics::Graphics(HWND hWnd, UINT w, UINT h)
	:
	screenWidth(w),
	screenHeight(h),
	rendertarget(w, h),
	bFullScreen(false)
{
	hMainDC = GetDC(hWnd);
}

void Graphics::BeginFrame()
{
	rendertarget.Clear();
}

void Graphics::EndFrame()
{
	HDC textureDC = CreateCompatibleDC(hMainDC);
	SelectObject(textureDC, rendertarget.GenerateBitmap());
	BitBlt(hMainDC, 0, 0, screenWidth, screenWidth, textureDC, 0, 0, SRCCOPY);
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
	return bFullScreen;
}

void Graphics::PutPixel(UINT x, UINT y, const Vector3& c)
{
	rendertarget.PutPixel(x, y, c);
}