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
	std::unique_ptr<DirectX::ScratchImage> pScratchImage;

public:
	Texture(UINT w, UINT h);
	Texture(const std::string& filePath);
	~Texture();

private:
	void FlipRB();

public:
	HBITMAP GenerateBitmap();

	size_t GetWidth() const;
	size_t GetHeight() const;

	void PutPixel(UINT x, UINT y, UINT c);
	void PutPixel(UINT x, UINT y, const Vector3& c);
	UINT GetPixelRGB(UINT x, UINT y) const;
	Vector3 GetPixel(UINT x, UINT y) const;

	void Clear();
};