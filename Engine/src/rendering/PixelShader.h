#pragma once
#include "BaseShader.h"

class PixelShader : public BaseShader
{
public:
	virtual Vector4 operator()(Vertex& vertex) abstract;
};

class DefaultPixelShader : public PixelShader
{
public:
	virtual Vector4 operator()(Vertex& vertex) override
	{
		return Vector4(255.0f, 255.0f, 255.0f, 1.0f);
	}
};