#include "Texture.h"
#include <DirectXTex/DirectXTex.h>

#pragma comment (lib, "DirectXTex.lib")

Texture::Texture(UINT w, UINT h)
{
	pTexture = std::make_unique<DirectX::ScratchImage>();
	pTexture->Initialize2D(DXGI_FORMAT_B8G8R8A8_UNORM, w, h, 1u, 1u);
	Clear();
}

Texture::Texture(const std::string& filePath)
{
	std::wstring wFilePath(filePath.begin(), filePath.end());
	DirectX::ScratchImage scratchImage;
	HRESULT hr = DirectX::LoadFromWICFile(
		wFilePath.c_str(),
		DirectX::WIC_FLAGS_IGNORE_SRGB,
		nullptr, scratchImage
	);

	if (scratchImage.GetImage(0, 0, 0)->format != DXGI_FORMAT_B8G8R8A8_UNORM)
	{
		DirectX::ScratchImage converted;
		DirectX::Convert(
			*scratchImage.GetImage(0, 0, 0),
			DXGI_FORMAT_B8G8R8A8_UNORM,
			DirectX::TEX_FILTER_DEFAULT,
			DirectX::TEX_THRESHOLD_DEFAULT,
			converted);
		
		pTexture = std::make_unique<DirectX::ScratchImage>(std::move(converted));
	}
	pTexture = std::make_unique<DirectX::ScratchImage>(std::move(scratchImage));

	FlipRB();
}

Texture::~Texture()
{
	pTexture.get()->Release();
}

void Texture::FlipRB()
{
	auto& image = pTexture->GetImages()[0];
	for (size_t iHeight = 0; iHeight < image.height; iHeight++)
	{
		for (size_t iWidth = 0; iWidth < image.width; iWidth++)
		{
			auto color = GetPixel((UINT)iWidth, (UINT)iHeight);
			std::swap(color.x, color.z);
			PutPixel((UINT)iWidth, (UINT)iHeight, color);
		}
	}
}

HBITMAP Texture::GenerateBitmap()
{
	return CreateBitmap((int)GetWidth(), (int)GetHeight(), 1u, 32u, pTexture->GetPixels());
}

size_t Texture::GetWidth() const
{
	return pTexture->GetMetadata().width;
}

size_t Texture::GetHeight() const
{
	return pTexture->GetMetadata().height;
}

void Texture::PutPixel(UINT x, UINT y, UINT c)
{
	*reinterpret_cast<UINT*>(pTexture->GetPixels() + (GetWidth() * 4u * y + size_t(x) * 4u)) = c;
}

void Texture::PutPixel(UINT x, UINT y, const Vector3& c)
{
	auto color = c * 255.0f;
	PutPixel(x, y, RGB(color.z, color.y, color.x));
}

Vector3 Texture::GetPixel(UINT x, UINT y) const
{
	auto rgb = GetPixelRGB(x, y);
	return { float((rgb >> 16u) & 0xFFu), float((rgb >> 8u) & 0xFFu), float(rgb & 0xFFu) };
}

UINT Texture::GetPixelRGB(UINT x, UINT y) const
{
	return *reinterpret_cast<UINT*>(pTexture->GetPixels() + (GetWidth() * 4u * y + size_t(x) * 4u));
}

void Texture::Clear()
{
	memset(pTexture->GetPixels(), 0, pTexture->GetPixelsSize());
}