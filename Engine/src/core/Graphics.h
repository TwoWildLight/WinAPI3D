#pragma once
#include "LightWindows.h"
#include "../rendering/Pipeline.h"
#include <memory>
#include <string>

class Graphics final
{
private:
	HDC hMainDC;
	HDC hBufferDC;

	std::unique_ptr<Pipeline> pPipeline;

	UINT screenWidth;
	UINT screenHeight;

	UINT resWidth;
	UINT resHeight;

	std::wstring tmpString;

public:
	Graphics(HWND hWnd, UINT w, UINT h, float scale = 1.0f);
	~Graphics() = default;

	Graphics(const Graphics&) = delete;
	Graphics(Graphics&&) = delete;
	Graphics& operator =(const Graphics&) = delete;

public:
	void BeginFrame();
	void EndFrame();

	void SetTmpString(const std::wstring& str)
	{
		tmpString = str;
	}

	void SetTopology(Context::Topology topology);
	void BindVertexShader(VertexShader* pVS);
	void BindPixelShader(PixelShader* pPS);
	void Render(IndexedTriangleList model);

	UINT GetWidth() const;
	UINT GetHeight() const;
};