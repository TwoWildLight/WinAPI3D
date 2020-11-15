#include "OutputMerger.h"

OutputMerger::OutputMerger(UINT w, UINT h)
	:
	renderTargetView(w, h)
{
	depthBuffer.resize(size_t(w) * h);
}

void OutputMerger::ClearRenderTarget()
{
	renderTargetView.Clear();
}

void OutputMerger::ClearDepthBuffer()
{
	for (auto& z : depthBuffer)
	{
		z = std::numeric_limits<float>::max();
	}
}

HBITMAP OutputMerger::GetBitmapRTV()
{
	return renderTargetView.GenerateBitmap();
}

void OutputMerger::PutPixel(UINT x, UINT y, float z, const Vector3& c)
{
	size_t target = renderTargetView.GetWidth() * y + x;
	if (target > size_t(renderTargetView.GetWidth()) * renderTargetView.GetHeight() || x >= renderTargetView.GetWidth()) return;

	if (z < depthBuffer[target])
	{
		renderTargetView.PutPixel(x, y, c);
		depthBuffer[target] = z;
	}
}