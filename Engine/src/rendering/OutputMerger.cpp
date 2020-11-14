#include "OutputMerger.h"

OutputMerger::OutputMerger(UINT w, UINT h)
	:
	renderTargetView(w, h)
{}

void OutputMerger::ClearRenderTarget()
{
	renderTargetView.Clear();
}

HBITMAP OutputMerger::GetBitmapRTV()
{
	return renderTargetView.GenerateBitmap();
}

void OutputMerger::PutPixel(UINT x, UINT y, const Vector3& c)
{
	renderTargetView.PutPixel(x, y, c);
}