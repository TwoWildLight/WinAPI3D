#include "Graphics.h"

Graphics::Graphics(HWND hWnd, UINT w, UINT h)
	:
	screenWidth(w),
	screenHeight(h)
{
	hMainDC = GetDC(hWnd);
	hBufferDC = CreateCompatibleDC(hMainDC);

	resolutionWidth = UINT((float)screenWidth * resolutionScale);
	resolutionHeight = UINT((float)screenHeight * resolutionScale);

	pRenderTargetView = std::make_unique<Texture>(resolutionWidth, resolutionHeight);
}

void Graphics::BeginFrame()
{
	pRenderTargetView->Clear();
}

void Graphics::EndFrame()
{
	HBITMAP bitmapView = pRenderTargetView->GenerateBitmap();
	SelectObject(hBufferDC, bitmapView);
	StretchBlt(hMainDC, 0, 0, screenWidth, screenHeight, hBufferDC, 0, 0, resolutionWidth, resolutionHeight, SRCCOPY);
	DeleteObject(bitmapView);
}

UINT Graphics::GetWidth() const
{
	return resolutionWidth;
}

UINT Graphics::GetHeight() const
{
	return resolutionHeight;
}

void Graphics::PutPixel(UINT x, UINT y, const Vector3& c)
{
	pRenderTargetView->PutPixel(x, y, c);
}