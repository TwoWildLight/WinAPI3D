#pragma once
#include "Texture.h"
#include <vector>

class OutputMerger
{
private:
	std::vector<UINT> renderTargetView;
	std::vector<float> depthBuffer;

	UINT rtvWidth;
	UINT rtvHeight;

public:
	OutputMerger(UINT w, UINT h);

public:
	void ClearRenderTarget();
	void ClearDepthBuffer();

	UINT GetRTVWidth() const;
	UINT GetRTVHeight() const;

	HBITMAP GetBitmapRTV();

	void PutPixel(UINT x, UINT y, float z, const Vector3& c);
};