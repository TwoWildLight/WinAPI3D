#include "Texture.h"
#include <DirectXTex/DirectXTex.h>

#pragma comment (lib, "DirectXTex.lib")

Texture::Texture(UINT w, UINT h)
{
	pTexture = std::make_unique<DirectX::ScratchImage>();
	pTexture->Initialize2D(DXGI_FORMAT_B8G8R8A8_UNORM, w, h, 1u, 1u, DirectX::CP_FLAGS::CP_FLAGS_LEGACY_DWORD);
	Clear();
}

Texture::Texture(std::string filePath)
{
}

Texture::~Texture()
{
	pTexture.get()->Release();
}

HBITMAP Texture::GenerateBitmap()
{
	auto& metadata = pTexture->GetMetadata();
	return CreateBitmap((int)metadata.width, (int)metadata.height, 1u, 32u, pTexture->GetPixels());
}

size_t Texture::GetWidth()
{
	return pTexture->GetMetadata().width;
}

size_t Texture::GetHeight()
{
	return pTexture->GetMetadata().height;
}

void Texture::PutPixel(UINT x, UINT y, const Vector3& c)
{
	*reinterpret_cast<UINT*>(pTexture->GetPixels() + (GetWidth() * 4u * y + size_t(x) * 4u)) = RGB(c.z, c.y, c.x);
}

void Texture::GetPixel(UINT x, UINT y) const
{
}

void Texture::Clear()
{
	memset(pTexture->GetPixels(), 0, pTexture->GetPixelsSize());
}