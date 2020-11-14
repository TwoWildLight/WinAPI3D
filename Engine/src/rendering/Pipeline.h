#pragma once
#include "Context.h"
#include "VertexShader.h"
#include "Tessellator.h"
#include "ScreenTransformer.h"
#include "Rasterizer.h"

class Pipeline
{
private:
	Graphics& gfx;
	Context context;
	VertexShader* pVertexShader;
	Tessellator tessellator;
	ScreenTransformer screenTransformer;
	Rasterizer rasterizer;

public:
	Pipeline(Graphics& gfx);

public:
	Context& GetContext();

	void BindVertexShader(VertexShader* pVS);

	void Draw(IndexedTriangleList itList);
};