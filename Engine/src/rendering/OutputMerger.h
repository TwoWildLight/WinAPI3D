#pragma once
#include "Texture.h"

class OutputMerger
{
private:
	Texture renderTargetView;

public:
	OutputMerger(UINT w, UINT h);

public:
	void ClearRenderTarget();

	HBITMAP GetBitmapRTV();

	void PutPixel(UINT x, UINT y, const Vector3& c);
};