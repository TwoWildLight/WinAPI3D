#pragma once
#include "../core/LightWindows.h"
#include "../utility/Vector.h"
#include <memory>
#include <string>

namespace DirectX
{
	class ScratchImage;
}

class Texture
{
private:
	std::unique_ptr<DirectX::ScratchImage> pTexture;

public:
	Texture(UINT w, UINT h);
	Texture(std::string filePath);
	~Texture();

public:
	HBITMAP GenerateBitmap();

	size_t GetWidth();
	size_t GetHeight();

	void PutPixel(UINT x, UINT y, const Vector3& c);
	void GetPixel(UINT x, UINT y) const;

	void Clear();
};