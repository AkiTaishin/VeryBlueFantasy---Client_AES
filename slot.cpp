#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "polygon.h"
#include "slot.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "ClientManager.h"
#include "gatya.h"
#include "toScene.h"

void CSlot::Init()
{
	m_ImgW = 78.0f;
	m_ImgH = 92.0f;
	m_MoveSpeed = 1.0f;
	m_IsClick = false;

	m_Poly = new CPolygon();
	m_Poly->Init("asset/sideMenu/slot_no_click.png", "asset/sideMenu/slot.png", m_ImgW, m_ImgH);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(-137.0f, -65.0f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CSlot::Uninit()
{
	m_Poly->Uninit();
}

void CSlot::Update()
{

#pragma region ポリゴンがクリックされたかデバッグ用

	if (CInput::GetKeyTrigger(VK_LBUTTON) && !CManager::m_Mouse->m_IsSelect)
	{
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// 画像の切り替え
			m_Poly->m_number = 2;
			CManager::m_Mouse->m_IsSelect = true;
		}
	}

	if (CInput::GetKeyRelease(VK_LBUTTON) && m_Poly->m_number == 2)
	{
		m_Poly->m_number = 1;
		CManager::m_Mouse->m_IsSelect = false;;

		// クリックが離されたときにボタンの上にマウスがあった場合
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// CFormationをここでサーバーから受け取る
			std::string toFormation;
			toFormation = CtoScene::GoToScene(3);
			if (toFormation == "CGatya")
			{
				CManager::SetSceneChangeFlag(true);
				CManager::SetScene<CGatya>();
			}
		}
	}

#pragma endregion
}

void CSlot::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}