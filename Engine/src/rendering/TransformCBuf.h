#pragma once
#include "../utility/Matrix.h"
#include <utility>

class TransformCBuf
{
public:
	struct Transforms
	{
		Matrix mView;
		Matrix mProj;
	};

private:
	Transforms transforms;

public:
	void SetViewMatrix(Matrix m)
	{
		transforms.mView = std::move(m);
	}
	void SetProjectionMatrix(Matrix m)
	{
		transforms.mProj = std::move(m);
	}

	Matrix GetViewMatrix() const
	{
		return transforms.mView;
	}
	Matrix GetProjectionMatrix() const
	{
		return transforms.mProj;
	}
	Matrix GetViewProjectionMatrix() const
	{
		return transforms.mView * transforms.mProj;
	}
};