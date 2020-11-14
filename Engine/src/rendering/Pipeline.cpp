#include "Pipeline.h"
#include "../core/Graphics.h"
#include <cassert>

Pipeline::Pipeline(Graphics& gfx)
	:
	gfx(gfx),
	outputMerger(gfx.GetWidth(), gfx.GetHeight())
{
	pVertexShader = nullptr;
}

Context& Pipeline::GetContext()
{
	return context;
}

VertexShader** Pipeline::GetVertexShader()
{
	return &pVertexShader;
}

OutputMerger& Pipeline::GetOutputMerger()
{
	return outputMerger;
}

void Pipeline::Clear()
{
	outputMerger.ClearRenderTarget();
}

void Pipeline::Render(IndexedTriangleList itList)
{
	for (size_t i = 0; i < itList.vb.Size(); i++)
	{
		screenTransformer.Transform(gfx, (*pVertexShader)(itList.vb[i]));
	}

	auto triangles = tessellator.Tessellate(itList);

	switch (context.GetTopology())
	{
	case Context::Topology::LINE_LIST:
		for (auto& t : triangles)
		{
			rasterizer.DrawLine(outputMerger, t.v0, t.v1);
			rasterizer.DrawLine(outputMerger, t.v1, t.v2);
			rasterizer.DrawLine(outputMerger, t.v2, t.v0);
		}
		break;
	default: assert(0 && "Bad Topology Type"); break;
	}
}