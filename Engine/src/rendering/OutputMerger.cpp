#include "OutputMerger.h"

OutputMerger::OutputMerger(UINT w, UINT h)
	:
	rtvWidth(w),
	rtvHeight(h)
{
	renderTargetView.resize(size_t(w) * h);
	depthBuffer.resize(size_t(w) * h);
}

void OutputMerger::ClearRenderTarget()
{
	memset(renderTargetView.data(), 0u, renderTargetView.size() * 4u);
}

void OutputMerger::ClearDepthBuffer()
{
	memset(depthBuffer.data(), 0xFF, depthBuffer.size() * sizeof(float));
}

UINT OutputMerger::GetRTVWidth() const
{
	return rtvWidth;
}

UINT OutputMerger::GetRTVHeight() const
{
	return rtvHeight;
}

HBITMAP OutputMerger::GetBitmapRTV()
{
	return CreateBitmap(rtvWidth, rtvHeight, 1u, 32u, renderTargetView.data());
}

void OutputMerger::PutPixel(UINT x, UINT y, float z, const Vector3& c)
{
	if (z < depthBuffer[(size_t)rtvWidth * y + x])
	{
		renderTargetView[(size_t)rtvWidth * y + x] = RGB(c.z, c.y, c.x);
		depthBuffer[(size_t)rtvWidth * y + x] = z;
	}
}