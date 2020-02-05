#include "main.h"

#include "texture.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "manager.h"

#include "gameObject.h"
#include "camera.h"
#include "Cube.h"

XMMATRIX g_world;

void CCube::Init() {
	VERTEX_3D vertex[34];
	{
		// 1枚目
		vertex[0].Position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[1].Position = XMFLOAT3(1.0f, -1.0f, -1.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[2].Position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[3].Position = XMFLOAT3(1.0f, 1.0f, -1.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

		// 中間
		vertex[4].Position = XMFLOAT3(1.0f, 1.0f, -1.0f);
		vertex[4].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[4].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[4].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[5].Position = XMFLOAT3(1.0f, -1.0f, -1.0f);
		vertex[5].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[5].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[5].TexCoord = XMFLOAT2(1.0f, 1.0f);

		// 2枚目
		vertex[6].Position = XMFLOAT3(1.0f, -1.0f, -1.0f);
		vertex[6].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[6].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[6].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[7].Position = XMFLOAT3(1.0f, -1.0f, 1.0f);
		vertex[7].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[7].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[7].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[8].Position = XMFLOAT3(1.0f, 1.0f, -1.0f);
		vertex[8].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[8].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[8].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[9].Position = XMFLOAT3(1.0f, 1.0f, 1.0f);
		vertex[9].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[9].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[9].TexCoord = XMFLOAT2(1.0f, 1.0f);

		// 中間
		vertex[10].Position = XMFLOAT3(1.0f, 1.0f, 1.0f);
		vertex[10].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[10].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[10].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[11].Position = XMFLOAT3(1.0f, -1.0f, 1.0f);
		vertex[11].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[11].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[11].TexCoord = XMFLOAT2(1.0f, 1.0f);

		// 3枚目
		vertex[12].Position = XMFLOAT3(1.0f, -1.0f, 1.0f);
		vertex[12].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[12].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[12].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[13].Position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
		vertex[13].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[13].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[13].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[14].Position = XMFLOAT3(1.0f, 1.0f, 1.0f);
		vertex[14].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[14].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[14].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[15].Position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
		vertex[15].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[15].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[15].TexCoord = XMFLOAT2(1.0f, 1.0f);

		// 中間
		vertex[16].Position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
		vertex[16].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[16].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[16].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[17].Position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
		vertex[17].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[17].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[17].TexCoord = XMFLOAT2(1.0f, 1.0f);

		// 4枚目
		vertex[18].Position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
		vertex[18].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[18].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[18].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[19].Position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
		vertex[19].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[19].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[19].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[20].Position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
		vertex[20].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[20].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[20].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[21].Position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
		vertex[21].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[21].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[21].TexCoord = XMFLOAT2(1.0f, 1.0f);

		// 中間
		vertex[22].Position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
		vertex[22].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[22].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[22].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[23].Position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
		vertex[23].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[23].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[23].TexCoord = XMFLOAT2(1.0f, 1.0f);

		// 5枚目
		vertex[24].Position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
		vertex[24].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[24].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[24].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[25].Position = XMFLOAT3(1.0f, -1.0f, 1.0f);
		vertex[25].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[25].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[25].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[26].Position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
		vertex[26].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[26].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[26].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[27].Position = XMFLOAT3(1.0f, -1.0f, -1.0f);
		vertex[27].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[27].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[27].TexCoord = XMFLOAT2(1.0f, 1.0f);

		// 中間
		vertex[28].Position = XMFLOAT3(1.0f, -1.0f, -1.0f);
		vertex[28].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[28].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[28].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[29].Position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
		vertex[29].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[29].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[29].TexCoord = XMFLOAT2(1.0f, 1.0f);

		// 6枚目
		vertex[30].Position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
		vertex[30].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[30].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[30].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[31].Position = XMFLOAT3(1.0f, 1.0f, -1.0f);
		vertex[31].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[31].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[31].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[32].Position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
		vertex[32].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[32].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[32].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[33].Position = XMFLOAT3(1.0f, 1.0f, 1.0f);
		vertex[33].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[33].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[33].TexCoord = XMFLOAT2(1.0f, 1.0f);
	}

#pragma region VertexBufferの作成

	// バッファの生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 34;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

#pragma endregion

#pragma region テクスチャの読み込み

	// テクスチャの読み込み
	m_Texture = new CTexture();
	m_Texture->Load("asset/barumunk2.tga");

#pragma endregion

	g_world = XMMatrixIdentity();
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Position = XMFLOAT3(-2.6f, -4.3f, 0.0f);
	m_Quaternion = XMQuaternionIdentity();			// クォータニオンの初期化
}

void CCube::Uninit() {
	m_VertexBuffer->Release();
	m_Texture->Unload();

	delete m_Texture;
}

void CCube::Update() {
	// キー入力
	{
		if (CInput::GetKeyPress('A')) {
			m_Position.x -= MoveSpeed;
		}

		if (CInput::GetKeyPress('D')) {
			m_Position.x += MoveSpeed;
		}

		if (CInput::GetKeyPress('W')) {
			m_Position.y += MoveSpeed;
		}

		if (CInput::GetKeyPress('S')) {
			m_Position.y -= MoveSpeed;
		}

		if (CInput::GetKeyPress('N')) {
			m_Position.z -= MoveSpeed;
		}

		if (CInput::GetKeyPress('M')) {
			m_Position.z += MoveSpeed;
		}
	}

	// クォータニオン回転入力
	if (CInput::GetKeyPress('J')) {
		XMFLOAT3 vz = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (CInput::GetKeyPress('L')) {
		XMFLOAT3 vz = XMFLOAT3(0.0f, 0.0f, -1.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (CInput::GetKeyPress('I')) {
		XMFLOAT3 vz = XMFLOAT3(0.0f, 1.0f, 0.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (CInput::GetKeyPress('K')) {
		XMFLOAT3 vz = XMFLOAT3(0.0f, -1.0f, 0.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
}

void CCube::Draw()
{
#pragma region 視錐台カリング

	// 視錐台カリングのためにカメラオブジェクトを取得する
	CCamera* camera;
	camera = CManager::GetScene()->GetGameObject<CCamera>(0);

	// この物体がカメラの視野内にいなかったら描画しない
	if (camera->GetVisibility(m_Position) == false)
	{
		return;
	}

#pragma endregion

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);		// IASetVertexBuffersで頂点バッファの設定をする
	CRenderer::SetTexture(m_Texture);		// テクスチャの設定

	g_world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);	// 拡大
	//g_world *= XMMatrixRotationRollPitchYaw(RotX, RotY, RotZ);	// 回転
	g_world *= XMMatrixRotationQuaternion(m_Quaternion);
	g_world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);		// 移動
	CRenderer::SetWorldMatrix(&g_world);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);		// IASetPrimitiveTopologyでトポロジの設定(頂点を結ぶルールを作る)
	CRenderer::GetDeviceContext()->Draw(34, 0);		// ポリゴンの描画(頂点数, スタートする頂点どっから始めますか)
}