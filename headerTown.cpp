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
#include "headerTown.h"
#include "ClientManager.h"

void CHeaderTown::Init()
{
#pragma region ‰æ‘œƒTƒCƒY‚ðHeader‚É‡‚í‚¹‚é

	m_ScreenImg = ASPECT;
	m_ImgW = 43.0f * m_ScreenImg;
	m_ImgH = 47.0f * m_ScreenImg;
	m_MoveSpeed = 1.0f;

#pragma endregion

	m_Poly = new CPolygon();
	m_Poly->Init("asset/header/town_no_click.png", "asset/header/town.png", m_ImgW, m_ImgH, 0.6f);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(173.0f, -141.5f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CHeaderTown::Uninit()
{
	m_Poly->Uninit();
}

void CHeaderTown::Update()
{
	if (CInput::GetKeyTrigger(VK_LBUTTON) && !CManager::m_Mouse->m_IsSelect)
	{
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			m_Poly->m_number = 2;
			CManager::m_Mouse->m_IsSelect = true;
		}
	}

	if (CInput::GetKeyRelease(VK_LBUTTON) && m_Poly->m_number == 2)
	{
		m_Poly->m_number = 1;
		CManager::m_Mouse->m_IsSelect = false;
	}
}

void CHeaderTown::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}