#pragma once
#include "BaseShader.h"

class VertexShader : public BaseShader
{
public:
	virtual DVTX::Vertex operator ()(DVTX::Vertex vertex)
	{
		auto& sv_pos = vertex.Attr<Vector4>(VertexType::POSITION4D);
		auto& pos = vertex.Attr<Vector3>(VertexType::POSITION3D);
		sv_pos = { pos.x, pos.y, pos.z, 1.0f };
		sv_pos *= transformCBuf.GetViewProjectionMatrix();
		return vertex;
	}
};