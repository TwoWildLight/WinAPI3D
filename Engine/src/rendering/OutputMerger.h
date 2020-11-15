#pragma once
#include "Texture.h"
#include <vector>

class OutputMerger
{
private:
	Texture renderTargetView;
	std::vector<float> depthBuffer;

public:
	OutputMerger(UINT w, UINT h);

public:
	void ClearRenderTarget();
	void ClearDepthBuffer();

	HBITMAP GetBitmapRTV();

	void PutPixel(UINT x, UINT y, float z, const Vector3& c);
};