#include "Pipeline.h"
#include "../core/Graphics.h"
#include "TriangleAssembler.h"
#include "ScreenTransformer.h"
#include "Rasterizer.h"
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
	outputMerger.ClearDepthBuffer();
}

void Pipeline::Render(IndexedTriangleList itList)
{
	for (size_t i = 0; i < itList.vertices.size(); i++)
	{
		// Vertex Shader Stage
		(*pVertexShader)(itList.vertices[i]);
	}

	// TA Culls & Clips Triangles
	for (auto& t : TriangleAssembler::Assemble(itList))
	{
		// Depth Division & NDC To Screen Space
		ScreenTransformer::Transform(gfx, t);

		// Rasterization
		switch (context.GetTopology())
		{
		case Context::Topology::LINE_LIST:
			Rasterizer::DrawLine(*pPixelShader, outputMerger, t);
			break;
		case Context::Topology::TRIANGLE_LIST:
			Rasterizer::DrawTriangle(*pPixelShader, outputMerger, t);
			break;
		default: assert(0 && "Bad Topology Type"); break;
		}
	}
}