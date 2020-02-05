#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "scene.h"
#include "manager.h"
#include "gameObject.h"
#include "polygon.h"
#include "header.h"
#include "headerSound.h"
#include "ClientManager.h"

void CHeaderSound::Init()
{
#pragma region 画像サイズをHeaderに合わせる

	m_ScreenImg = ASPECT;
	m_ImgW = 31.0f * m_ScreenImg;
	m_ImgH = 31.0f * m_ScreenImg;
	m_IsClick = false;

#pragma endregion

	// ボタンが押された時の処理に使う
	m_IsClick = false;

	m_Poly = new CPolygon();
	m_Poly->Init("asset/header/sound_on.png", "asset/header/sound_off.png", m_ImgW, m_ImgH);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(-168.0f, -305.5f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CHeaderSound::Uninit()
{
	m_Poly->Uninit();
}

void CHeaderSound::Update()
{
	if (CInput::GetKeyTrigger(VK_LBUTTON) && !CManager::m_Mouse->m_IsSelect && !m_IsClick)
	{
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			m_IsClick = true;

			if (m_Poly->m_number == 1)
			{
				m_Poly->m_number = 2;
				CManager::m_Mouse->m_IsSelect = true;
			}
			else
			{
				m_Poly->m_number = 1;
				CManager::m_Mouse->m_IsSelect = true;
			}
		}
	}

	if (CInput::GetKeyRelease(VK_LBUTTON) && m_IsClick)
	{
		m_IsClick = false;
		CManager::m_Mouse->m_IsSelect = false;
	}
}

void CHeaderSound::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}