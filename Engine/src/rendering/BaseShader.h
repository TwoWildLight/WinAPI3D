#pragma once
#include "TransformCBuf.h"
#include "DynamicVertex.h"
#include "DynamicConstant.h"
#include "../utility/Vector.h"
#include <array>

class BaseShader
{
protected:
	using VertexType = DVTX::VertexLayout::Element::Type;
	using ConstantType = DCST::ConstantLayout::Element::Type;

protected:
	TransformCBuf transformCBuf;
	std::array<DCST::ConstantBuffer*, 5u> cbuffers;

public:
	void SetTransformCBuf(TransformCBuf tcb)
	{
		transformCBuf = std::move(tcb);
	}

	void SetConstantBuffer(DCST::ConstantBuffer* pCB, UINT slot = 0u)
	{
		assert(slot < 5u);
		cbuffers[slot] = pCB;
	}
};