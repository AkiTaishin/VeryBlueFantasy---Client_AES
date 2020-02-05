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
	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);

	// �r���[�}�g���N�X�ݒ�
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);

	CRenderer::SetViewMatrix(&m_ViewMatrix);

	// �v���W�F�N�V�����}�g���N�X�ݒ�
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

/// <summary>
/// ������J�����O
/// </summary>
/// <param name="Position">�m�F���������̂̋�ԏ���W</param>
/// <returns>True�̎��͕`�������</returns>
bool CCamera::GetVisibility(XMFLOAT3 Position)
{
	XMVECTOR worldPos, viewPos, projPos;
	XMFLOAT3 projPosF;

	// ������world���W���i�[�i�}�g���N�X�ϊ��j
	// XMFLOAT3�^����XMVECTOR3�^�ɕϊ�
	worldPos = XMLoadFloat3(&Position);
	// �r���[���W�ϊ�
	viewPos = XMVector3TransformCoord(worldPos, m_ViewMatrix);
	// �v���W�F�N�V�����ϊ�
	projPos = XMVector3TransformCoord(viewPos, m_ProjectionMatrix);
	// XMVECTOR3�^����XMFLOAT3�^�ɖ߂�
	XMStoreFloat3(&projPosF, projPos);

	// ���̂���������ɂ�����`�������
	// Z�����̓J������near��far�̒l������Bnear�����ɂȂ邱�Ƃ͂Ȃ��̂Œ��ӁI
	if (-1.0f < projPosF.x && projPosF.x < 1.0f && -1.0f < projPosF.y && projPosF.y < 1.0f && 0.0f < projPosF.z && projPosF.z < 1.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}