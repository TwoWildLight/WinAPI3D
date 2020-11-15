#include "Pipeline.h"
#include "../core/Graphics.h"
#include <cassert>

Pipeline::Pipeline(Graphics& gfx)
	:
	gfx(gfx),
	outputMerger(gfx.GetWidth(), gfx.GetHeight())
{
	pVertexShader = nullptr;
	pPixelShader = nullptr;
}

Context& Pipeline::GetContext()
{
	return context;
}

VertexShader** Pipeline::GetVertexShaderAddr()
{
	return &pVertexShader;
}

PixelShader** Pipeline::GetPixelShaderAddr()
{
	return &pPixelShader;
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
	for (size_t i = 0; i < itList.vertices.size(); i++)
	{
		screenTransformer.Transform(gfx, (*pVertexShader)(itList.vertices[i]));
	}

	switch (context.GetTopology())
	{
	case Context::Topology::LINE_LIST:
		for (size_t i = 0; i < itList.indices.size(); i += 3)
		{
			rasterizer.DrawLine(*pPixelShader, outputMerger, itList[i + 0], itList[i + 1]);
			rasterizer.DrawLine(*pPixelShader, outputMerger, itList[i + 1], itList[i + 2]);
			rasterizer.DrawLine(*pPixelShader, outputMerger, itList[i + 2], itList[i + 0]);
		}
		break;
	case Context::Topology::TRIANGLE_LIST:
		for (size_t i = 0; i < itList.indices.size(); i += 3)
		{
			rasterizer.DrawTriangle(*pPixelShader, outputMerger, { itList[i + 0], itList[i + 1], itList[i + 2] });
		}
		break;
	default: assert(0 && "Bad Topology Type"); break;
	}
}