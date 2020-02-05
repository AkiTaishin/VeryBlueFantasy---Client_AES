#include "scene.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "charButton.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "gameObject.h"
#include "polygon.h"
#include "ClientManager.h"

void CCharButton::Init(float x, float y, float z, int number, bool flag)
{
	m_ScreenImg = ASPECT;
	m_ImgW = 95.0f * m_ScreenImg;
	m_ImgH = 34.0f * m_ScreenImg;
	m_IsAlive = flag;

	m_Poly = new CPolygon();

	m_Poly->Init("asset/button/charButton.png", "asset/button/charButtonNow.png", m_ImgW, m_ImgH);
	m_Poly->m_number = number;

	m_Position = XMFLOAT3(x, y, z);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CCharButton::Uninit()
{
	m_Poly->Uninit();
}

void CCharButton::Update()
{
#pragma region ����

	m_Poly->SetPosition(m_Position);

#pragma endregion

#pragma region �|���S�����N���b�N���ꂽ���f�o�b�O�p

	/// <summary>
	/// �������I������Ă���Ƃ��ɉ�����Ă������N���Ȃ�(��肱�݂̎��ɃX�P�[��������������)
	/// �����ȊO���I������Ă���Ƃ��ɑI�����ꂽ���̂݁A
	/// ������ON�ɂ��Ď����ȊO��OFF�ɂ���
	/// </summary>

	if (CInput::GetKeyTrigger(VK_LBUTTON) && !CManager::m_Mouse->m_IsSelect)
	{
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// �摜�̐؂�ւ�
			CManager::m_Mouse->m_IsSelect = true;
		}
	}

	if (CInput::GetKeyRelease(VK_LBUTTON))
	{
		CManager::m_Mouse->m_IsSelect = false;

		// �N���b�N�������ꂽ�Ƃ��Ƀ{�^���̏�Ƀ}�E�X���������ꍇ
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// DestroyGameObject���Ă�ŐV���ȃ|���S����Add����
			m_IsAlive = !m_IsAlive;
		}
	}

#pragma endregion
}

void CCharButton::Draw()
{
	if (m_IsAlive)
		m_Poly->Draw(m_Poly->m_number);
}

/// <summary>
/// �t���O���ɂ��Draw���邩���Ȃ������Ǘ�����B
/// �܂�
/// �|���S���͏d�˂ĕ\�����Ă���
/// </summary>