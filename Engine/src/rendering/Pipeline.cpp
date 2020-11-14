#include "Pipeline.h"
#include <cassert>

Pipeline::Pipeline(Graphics& gfx)
	:
	gfx(gfx)
{}

Context& Pipeline::GetContext()
{
	return context;
}

void Pipeline::BindVertexShader(VertexShader* pVS)
{
	pVertexShader = pVS;
}

void Pipeline::Draw(IndexedTriangleList itList)
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
			rasterizer.DrawLine(gfx, t.v0, t.v1);
			rasterizer.DrawLine(gfx, t.v1, t.v2);
			rasterizer.DrawLine(gfx, t.v2, t.v0);
		}
		break;
	default: assert(0 && "Bad Topology Type"); break;
	}
}