#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "summonButton.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "gameObject.h"
#include "polygon.h"
#include "ClientManager.h"

void CSummonButton::Init(float x, float y, float z, int number, bool flag)
{
	m_ScreenImg = ASPECT;
	m_ImgW = 95.0f * m_ScreenImg;
	m_ImgH = 34.0f * m_ScreenImg;
	m_IsAlive = flag;

	m_Poly = new CPolygon();

	m_Poly->Init("asset/button/summonButton.png", "asset/button/summonButtonNow.png", m_ImgW, m_ImgH);
	m_Poly->m_number = number;

	m_Position = XMFLOAT3(x, y, z);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CSummonButton::Uninit()
{
	m_Poly->Uninit();
}

void CSummonButton::Update()
{
#pragma region 入力

	m_Poly->SetPosition(m_Position);

#pragma endregion

#pragma region ポリゴンがクリックされたかデバッグ用

	if (CInput::GetKeyTrigger(VK_LBUTTON) && !CManager::m_Mouse->m_IsSelect)
	{
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// 画像の切り替え
			//m_Poly->m_number = 2;
			CManager::m_Mouse->m_IsSelect = true;
		}
	}

	if (CInput::GetKeyRelease(VK_LBUTTON) && m_Poly->m_number == 2)
	{
		//m_Poly->m_number = 1;
		CManager::m_Mouse->m_IsSelect = false;

		// クリックが離されたときにボタンの上にマウスがあった場合
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// DestroyGameObjectを呼んで新たなポリゴンをAddする
			m_IsAlive = false;
		}
	}

#pragma endregion
}

void CSummonButton::Draw()
{
	if (m_IsAlive)
		m_Poly->Draw(m_Poly->m_number);
}