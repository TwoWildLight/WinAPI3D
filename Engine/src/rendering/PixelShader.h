#pragma once
#include "BaseShader.h"

class PixelShader : public BaseShader
{
public:
	virtual Vector4 operator()(DVTX::Vertex vertex)
	{
		return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}
};