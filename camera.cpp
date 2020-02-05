#include "main.h"
#include "input.h"
#include "renderer.h"
#include "gameObject.h"
#include "camera.h"
#include "manager.h"

bool CameraAngle = true;

void CCamera::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, -10.0f);
	m_Rotation = XMFLOAT3(0.1f, 0.0f, 0.0f);
	m_WorkPos = m_Position;
	m_WorkPos.z = -10.0f;
	m_WorkRot = m_Rotation;

	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;
}

void CCamera::Uninit()
{
}

void CCamera::Update()
{
}

void CCamera::Draw()
{
	// ビューポート設定
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);

	// ビューマトリクス設定
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);

	CRenderer::SetViewMatrix(&m_ViewMatrix);

	// プロジェクションマトリクス設定
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

/// <summary>
/// 視錐台カリング
/// </summary>
/// <param name="Position">確認したい物体の空間上座標</param>
/// <returns>Trueの時は描画をする</returns>
bool CCamera::GetVisibility(XMFLOAT3 Position)
{
	XMVECTOR worldPos, viewPos, projPos;
	XMFLOAT3 projPosF;

	// ここでworld座標が格納（マトリクス変換）
	// XMFLOAT3型からXMVECTOR3型に変換
	worldPos = XMLoadFloat3(&Position);
	// ビュー座標変換
	viewPos = XMVector3TransformCoord(worldPos, m_ViewMatrix);
	// プロジェクション変換
	projPos = XMVector3TransformCoord(viewPos, m_ProjectionMatrix);
	// XMVECTOR3型からXMFLOAT3型に戻す
	XMStoreFloat3(&projPosF, projPos);

	// 物体が視錐台内にいたら描画をする
	// Z成分はカメラのnearとfarの値を入れる。nearが負になることはないので注意！
	if (-1.0f < projPosF.x && projPosF.x < 1.0f && -1.0f < projPosF.y && projPosF.y < 1.0f && 0.0f < projPosF.z && projPosF.z < 1.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}