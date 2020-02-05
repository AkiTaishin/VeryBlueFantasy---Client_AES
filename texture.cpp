#include "main.h"
#include "renderer.h"
#include <string>
#include "DirectXTex.h"
#include "texture.h"
#include "CChar_WChar.h"

void CTexture::Load(const char *FileName)
{
	unsigned char	header[18];
	unsigned char	*image;
	unsigned int	width, height;
	unsigned char	depth;
	unsigned int	bpp;
	unsigned int	size;

	// ヘッダ読み込み
	FILE* file;
	file = fopen(FileName, "rb");
	assert(file);

	fread(header, sizeof(header), 1, file);

	// 画像サイズ取得
	width = header[13] * 256 + header[12];
	height = header[15] * 256 + header[14];
	depth = header[16];

	if (depth == 32)
		bpp = 4;
	else if (depth == 24)
		bpp = 3;
	else
		bpp = 0;

	if (bpp != 4) {
		assert(false);
	}

	size = width * height * bpp;

	// メモリ確保
	image = (unsigned char*)new unsigned char[size];

	// 画像読み込み
	fread(image, size, 1, file);

	// R<->B
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			unsigned char c;
			c = image[(y * width + x) * bpp + 0];
			image[(y * width + x) * bpp + 0] = image[(y * width + x) * bpp + 2];
			image[(y * width + x) * bpp + 2] = c;
		}
	}

	fclose(file);

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = image;
	initData.SysMemPitch = width * 4;
	initData.SysMemSlicePitch = size;

	auto hr = CRenderer::GetDevice()->CreateTexture2D(&desc, &initData, &m_Texture);
	if (FAILED(hr)) {
		assert(false);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	hr = CRenderer::GetDevice()->CreateShaderResourceView(m_Texture, &SRVDesc, &m_ShaderResourceView);
	if (FAILED(hr))
	{
		assert(false);
	}

	delete image;
}

void CTexture::LoadTexChar(std::string FileName)
{
	std::wstring file;
	CChar_WChar::widen(FileName.c_str(), file);

	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);  // For multithreaded programs

	// Bind Flags
	UINT bindFlags = 0;
	bindFlags |= D3D11_BIND_SHADER_RESOURCE;

	DirectX::TexMetadata metadata;
	DirectX::ScratchImage images;

	// WIC読み込み
	// Windows標準ライブラリ全対応
	hr = DirectX::LoadFromWICFile(file.c_str(), DirectX::WIC_FLAGS_ALL_FRAMES, &metadata, images);

	if (FAILED(hr)) {
		// DDS読み込み
		hr = DirectX::LoadFromDDSFile(file.c_str(), DirectX::DDS_FLAGS_NONE, &metadata, images);
	}
	if (FAILED(hr)) {
		// TGA読み込み
		hr = DirectX::LoadFromTGAFile(file.c_str(), &metadata, images);
	}
	if (FAILED(hr)) {
		// HDR読み込み
		hr = DirectX::LoadFromHDRFile(file.c_str(), &metadata, images);
	}

	if (FAILED(hr)) {
		assert(false);
	}

	hr = DirectX::CreateTexture(CRenderer::GetDevice(),
		images.GetImages(),
		images.GetImageCount(),
		images.GetMetadata(),
		(ID3D11Resource**)&m_Texture    /*output*/);

	if (FAILED(hr)) {
		assert(false);
	}

	hr = DirectX::CreateShaderResourceView(CRenderer::GetDevice(),
		images.GetImages(),
		images.GetImageCount(),
		metadata,
		&m_ShaderResourceView);

	if (FAILED(hr)) {
		assert(false);
	}
}

void CTexture::Unload()
{
	m_Texture->Release();
	m_ShaderResourceView->Release();
}