#pragma once
#include "../utility/Matrix.h"
#include <utility>

class TransformCBuf
{
public:
	struct Transforms
	{
		Matrix mView;
		Matrix mViewProj;
	};

private:
	Transforms transforms;

public:
	void SetViewMatrix(Matrix m)
	{
		transforms.mView = std::move(m);
	}
	void SetViewProjectionMatrix(Matrix m)
	{
		transforms.mViewProj = std::move(m);
	}

	Matrix GetViewMatrix() const
	{
		return transforms.mView;
	}
	Matrix GetViewProjectionMatrix() const
	{
		return transforms.mViewProj;
	}
};