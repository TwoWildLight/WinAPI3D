#pragma once
#include "BaseShader.h"

class VertexShader : public BaseShader
{
public:
	virtual Vertex& operator ()(Vertex& v) abstract;
};

class DefaultVertexShader : public VertexShader
{
public:
	virtual Vertex& operator()(Vertex& v) override
	{
		v.sv_pos = Vector4(v.pos) * transformCBuf.GetViewProjectionMatrix();
		
		v.pos *= transformCBuf.GetViewMatrix();
		auto m = transformCBuf.GetViewMatrix();
		m._41 = m._42 = m._43 = 0.0f;
		v.n *= m;

		return v;
	}
};