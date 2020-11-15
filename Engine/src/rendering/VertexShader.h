#pragma once
#include "BaseShader.h"

class VertexShader : public BaseShader
{
public:
	virtual DVTX::Vertex operator ()(DVTX::Vertex vertex)
	{
		auto& pos = vertex.Attr<Vector3>(VertexType::POSITION3D);
		Vector4 sv_pos(pos.x, pos.y, pos.z, 1.0f);

		sv_pos *= transformCBuf.GetViewProjectionMatrix();
		pos = { sv_pos.x, sv_pos.y, sv_pos.z };

		return vertex;
	}
};