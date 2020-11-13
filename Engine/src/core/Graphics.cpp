#include "Graphics.h"

Graphics::Graphics(HWND hWnd, UINT w, UINT h)
	:
	screenWidth(w),
	screenHeight(h),
	renderTargetView(w, h)
{
	hMainDC = GetDC(hWnd);
	hBufferDC = CreateCompatibleDC(hMainDC);
}

void Graphics::BeginFrame()
{
	renderTargetView.Clear();
}

void Graphics::EndFrame()
{
	HBITMAP bitmapView = renderTargetView.GenerateBitmap();
	SelectObject(hBufferDC, bitmapView);
	BitBlt(hMainDC, 0, 0, screenWidth, screenWidth, hBufferDC, 0, 0, SRCCOPY);
	DeleteObject(bitmapView);
}

UINT Graphics::GetWidth() const
{
	return screenWidth;
}

UINT Graphics::GetHeight() const
{
	return screenHeight;
}

void Graphics::PutPixel(UINT x, UINT y, const Vector3& c)
{
	renderTargetView.PutPixel(x, y, c);
}