#pragma once
#include "DynamicVertex.h"
#include "DynamicConstant.h"
#include "TransformCBuf.h"
#include "../utility/Vector.h"
#include <array>

class VertexShader
{
private:
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

	virtual DVTX::Vertex operator ()(DVTX::Vertex vertex)
	{
		using Type = DVTX::VertexLayout::Element::Type;
		auto& sv_pos = vertex.Attr<Vector4>(Type::POSITION4D);
		sv_pos.w = 1.0f;
		auto& pos = vertex.Attr<Vector4>(Type::POSITION3D);

		sv_pos = pos * transformCBuf.GetViewProjectionMatrix();
		return vertex;
	}
};