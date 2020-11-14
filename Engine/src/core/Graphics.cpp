#include "Graphics.h"

Graphics::Graphics(HWND hWnd, UINT w, UINT h, float scale)
	:
	screenWidth(w),
	screenHeight(h)
{
	hMainDC = GetDC(hWnd);
	hBufferDC = CreateCompatibleDC(hMainDC);

	resWidth = UINT((float)screenWidth * scale);
	resHeight = UINT((float)screenHeight * scale);

	pPipeline = std::make_unique<Pipeline>(*this);
}

void Graphics::BeginFrame()
{
	pPipeline->Clear();
}

void Graphics::EndFrame()
{
	HBITMAP bitmap = pPipeline->GetOutputMerger().GetBitmapRTV();
	SelectObject(hBufferDC, bitmap);
	StretchBlt(hMainDC, 0, 0, screenWidth, screenHeight, hBufferDC, 0, 0, resWidth, resHeight, SRCCOPY);
	DeleteObject(bitmap);
}

void Graphics::SetTopology(Context::Topology topology)
{
	pPipeline->GetContext().SetTopology(topology);
}

void Graphics::BindVertexShader(VertexShader* pVS)
{
	*pPipeline->GetVertexShader() = pVS;
}

void Graphics::Render(IndexedTriangleList model)
{
	pPipeline->Render(model);
}

UINT Graphics::GetWidth() const
{
	return resWidth;
}

UINT Graphics::GetHeight() const
{
	return resHeight;
}