#pragma once
#include "Context.h"
#include "VertexShader.h"
#include "Tessellator.h"
#include "ScreenTransformer.h"
#include "Rasterizer.h"
#include "OutputMerger.h"

class Pipeline
{
private:
	Graphics& gfx;
	Context context;
	VertexShader* pVertexShader;
	Tessellator tessellator;
	ScreenTransformer screenTransformer;
	Rasterizer rasterizer;
	OutputMerger outputMerger;

public:
	Pipeline(Graphics& gfx);

public:
	Context& GetContext();
	VertexShader** GetVertexShader();
	OutputMerger& GetOutputMerger();

	void Clear();
	void Render(IndexedTriangleList itList);
};