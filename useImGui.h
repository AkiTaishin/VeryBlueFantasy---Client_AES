#pragma once
class CuseImGui
{
public:
	void Create(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context);
	void Destroy();
	static void SetFrame();
	static void Render();
};