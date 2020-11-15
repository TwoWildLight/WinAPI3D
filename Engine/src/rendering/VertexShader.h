#pragma once
#include "BaseShader.h"

class VertexShader : public BaseShader
{
public:
	virtual PNVertex& operator ()(PNVertex& vertex) abstract;
};

class DefaultVertexShader : public VertexShader
{
public:
	virtual PNVertex& operator()(PNVertex& vertex) override
	{
		Vector4 sv_pos(vertex.pos.x, vertex.pos.y, vertex.pos.z, 1.0f);

		sv_pos *= transformCBuf.GetViewProjectionMatrix();
		vertex.pos = { sv_pos.x, sv_pos.y, sv_pos.z };
		vertex.n *= transformCBuf.GetViewMatrix();

		return vertex;
	}
};