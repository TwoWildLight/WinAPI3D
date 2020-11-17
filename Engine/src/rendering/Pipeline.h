#pragma once
#include "Context.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "OutputMerger.h"
#include "IndexedTriangleList.h"

class Graphics;

class Pipeline
{
private:
	Graphics& gfx;
	Context context;

	VertexShader* pVertexShader;
	PixelShader* pPixelShader;
	OutputMerger outputMerger;

public:
	Pipeline(Graphics& gfx);

public:
	Context& GetContext();
	VertexShader** GetVertexShaderAddr();
	PixelShader** GetPixelShaderAddr();
	OutputMerger& GetOutputMerger();

	void Clear();
	void Render(IndexedTriangleList itList);
};