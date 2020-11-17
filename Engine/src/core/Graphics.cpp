#include "Graphics.h"

Graphics::Graphics(HWND hWnd, UINT w, UINT h, float scale)
	:
	screenWidth(w),
	screenHeight(h)
{
	hMainDC = GetDC(hWnd);
	hBufferDC = CreateCompatibleDC(hMainDC);

	SetTextColor(hMainDC, RGB(255, 255, 255));
	SetBkMode(hMainDC, TRANSPARENT);

	HFONT hFixedFont = CreateFontW(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"Unispace");
	SelectObject(hMainDC, hFixedFont);
	DeleteObject(hFixedFont);

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

	RECT rt = { 0,0,200,100 };
	DrawTextW(hMainDC, tmpString.c_str(), -1, &rt, NULL);
}

void Graphics::SetTopology(Context::Topology topology)
{
	pPipeline->GetContext().SetTopology(topology);
}

void Graphics::BindVertexShader(VertexShader* pVS)
{
	*(pPipeline->GetVertexShaderAddr()) = pVS;
}

void Graphics::BindPixelShader(PixelShader* pPS)
{
	*(pPipeline->GetPixelShaderAddr()) = pPS;
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