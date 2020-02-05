#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "polygon.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "ClientManager.h"

void CPolygon::Init(std::string fileName1, std::string fileName2, float width, float hight)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3((float)SCREEN_WIDTH * 0.5 - (float)width * 0.5f, (float)SCREEN_HEIGHT * 0.5 - (float)hight * 0.5f, (float)0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3((float)SCREEN_WIDTH * 0.5 + (float)width * 0.5f, (float)SCREEN_HEIGHT * 0.5 - (float)hight * 0.5f, (float)0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3((float)SCREEN_WIDTH * 0.5 - (float)width * 0.5f, (float)SCREEN_HEIGHT * 0.5 + (float)hight * 0.5f, (float)0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3((float)SCREEN_WIDTH * 0.5 + (float)width * 0.5f, (float)SCREEN_HEIGHT * 0.5 + (float)hight * 0.5f, (float)0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Texture1 = new CTexture();
	m_Texture1->LoadTexChar(fileName1);

	m_Texture2 = new CTexture();
	m_Texture2->LoadTexChar(fileName2);

	m_Input = new CInput();
}

void CPolygon::Init(std::string fileName1, std::string fileName2, float width, float hight, float alpha)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(SCREEN_WIDTH * 0.5 - width * 0.5f, SCREEN_HEIGHT * 0.5 - hight * 0.5f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, alpha);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(SCREEN_WIDTH * 0.5 + width * 0.5f, SCREEN_HEIGHT * 0.5 - hight * 0.5f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, alpha);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(SCREEN_WIDTH * 0.5 - width * 0.5f, SCREEN_HEIGHT * 0.5 + hight * 0.5f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, alpha);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(SCREEN_WIDTH * 0.5 + width * 0.5f, SCREEN_HEIGHT * 0.5 + hight * 0.5f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, alpha);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Texture1 = new CTexture();
	m_Texture1->LoadTexChar(fileName1);

	m_Texture2 = new CTexture();
	m_Texture2->LoadTexChar(fileName2);

	m_Input = new CInput();
}

void CPolygon::Init(std::string fileName, float width, float hight, float alpha)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(SCREEN_WIDTH * 0.5 - width * 0.5f, SCREEN_HEIGHT * 0.5 - hight * 0.5f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, alpha);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(SCREEN_WIDTH * 0.5 + width * 0.5f, SCREEN_HEIGHT * 0.5 - hight * 0.5f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, alpha);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(SCREEN_WIDTH * 0.5 - width * 0.5f, SCREEN_HEIGHT * 0.5 + hight * 0.5f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, alpha);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(SCREEN_WIDTH * 0.5 + width * 0.5f, SCREEN_HEIGHT * 0.5 + hight * 0.5f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, alpha);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Texture1 = new CTexture();
	m_Texture1->LoadTexChar(fileName);

	m_Texture2 = new CTexture();
	m_Texture2->LoadTexChar(fileName);

	m_Input = new CInput();
}

void CPolygon::Uninit()
{
	m_VertexBuffer->Release();

	m_Texture2->Unload();
	delete m_Texture2;

	m_Texture1->Unload();
	delete m_Texture1;
}

void CPolygon::Update()
{
}

void CPolygon::Draw(int number)
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	if (number == 1)
	{
		CRenderer::SetTexture(m_Texture1);		// テクスチャの設定
	}
	else
	{
		CRenderer::SetTexture(m_Texture2);		// テクスチャの設定
	}

	m_World = XMMatrixIdentity();
	m_World = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);		// 移動
	m_World *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);		// 移動

	CRenderer::SetWorldViewProjection2D();		// 2D用のマトリクス設定
	CRenderer::SetWorldMatrix(&m_World);

#pragma region ステンシルバッファをレンダーにセット

	ID3D11DeviceContext* context = CRenderer::GetDeviceContext();
	ID3D11RenderTargetView* render = CRenderer::GetTargetView();
	context->OMSetRenderTargets(1, &render, CRenderer::GetStencilView());
	context->ClearDepthStencilView(CRenderer::GetStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

#pragma endregion

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);		// IASetPrimitiveTopologyでトポロジの設定(頂点を結ぶルールを作る)
	CRenderer::GetDeviceContext()->Draw(4, 0);		// ポリゴンの描画(頂点数, スタートする頂点どっから始めますか)
}