#pragma once

#include "main.h"
#include "renderer.h"
#include <string>

class CTexture
{
public:

	void Load(const char *FileName);
	void LoadTexChar(std::string FileName);
	void Unload();

	ID3D11ShaderResourceView* GetShaderResourceView() { return m_ShaderResourceView; }

private:

	ID3D11Texture2D*			m_Texture;
	ID3D11ShaderResourceView*	m_ShaderResourceView;
};