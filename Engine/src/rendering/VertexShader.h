#pragma once
#include "BaseShader.h"

class VertexShader : public BaseShader
{
public:
	virtual PNVertex& operator ()(PNVertex& v) abstract;
};

class DefaultVertexShader : public VertexShader
{
public:
	virtual PNVertex& operator()(PNVertex& v) override
	{
		v.sv_pos = Vector4(v.pos.x, v.pos.y, v.pos.z, 1.0f) * transformCBuf.GetViewProjectionMatrix();
		v.pos *= transformCBuf.GetViewMatrix();
		auto m = transformCBuf.GetViewMatrix();
		m._41 = m._42 = m._43 = 0.0f;
		v.n *= m;

		return v;
	}
};