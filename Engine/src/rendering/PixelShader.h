#pragma once
#include "BaseShader.h"

class PixelShader : public BaseShader
{
public:
	virtual Vector4 operator()(PNVertex& vertex) abstract;
};

class DefaultPixelShader : public PixelShader
{
public:
	virtual Vector4 operator()(PNVertex& vertex) override
	{
		return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}
};