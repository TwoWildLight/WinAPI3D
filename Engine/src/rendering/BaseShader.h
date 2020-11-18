#pragma once
#include "DynamicConstant.h"
#include "TransformCBuf.h"
#include "Texture.h"
#include "Vertex.h"
#include <array>

class Sampler
{
public:
	static Vector4 Sample(Vector2 tc, Texture* pTexture)
	{
		return pTexture->GetPixel(UINT(tc.x * (pTexture->GetWidth() - 1u)), UINT(tc.y * (pTexture->GetHeight() - 1u)));
	}
};

class BaseShader
{
protected:
	using ConstantType = DCST::ConstantLayout::Element::Type;

protected:
	TransformCBuf transformCBuf;
	std::array<DCST::ConstantBuffer*, 5u> cbuffers;
	std::array<Texture*, 2u> textures;

public:
	void SetTransformCBuf(TransformCBuf tcb)
	{
		transformCBuf = std::move(tcb);
	}
	TransformCBuf GetTransforms() const
	{
		return transformCBuf;
	}

	void BindConstantBuffer(DCST::ConstantBuffer* pCB, UINT slot = 0u)
	{
		assert(slot < 5u);
		cbuffers[slot] = pCB;
	}

	void BindTexture(Texture* pTexture, UINT slot = 0u)
	{
		textures[slot] = pTexture;
	}
};