#include "scene.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "polygon.h"
#include "quest.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "ClientManager.h"
#include "header.h"
#include "toScene.h"
#include "questPage.h"

void CQuest::Init()
{
	CHeader* header = CManager::GetScene()->GetGameObject<CHeader>(4);
	m_ScreenImg = header->m_ScreenImg;

	m_ImgW = 103.0f * m_ScreenImg;
	m_ImgH = 123.0f * m_ScreenImg;
	m_MoveSpeed = 1.0f;

	m_Poly = new CPolygon();
	m_Poly->Init("asset/sideMenu/quest_no_click.png", "asset/sideMenu/quest.png", m_ImgW, m_ImgH);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(136.0f, 11.0f, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CQuest::Uninit()
{
	m_Poly->Uninit();
}

void CQuest::Update()
{
#pragma region 入力

	/*if (CInput::GetKeyPress(VK_LEFT)) {
		m_Position.x -= m_MoveSpeed;
		m_Poly->SetPosition(m_Position);
	}

	if (CInput::GetKeyPress(VK_RIGHT)) {
		m_Position.x += m_MoveSpeed;
		m_Poly->SetPosition(m_Position);
	}

	if (CInput::GetKeyPress(VK_UP)) {
		m_Position.y -= m_MoveSpeed;
		m_Poly->SetPosition(m_Position);
	}

	if (CInput::GetKeyPress(VK_DOWN)) {
		m_Position.y += m_MoveSpeed;
		m_Poly->SetPosition(m_Position);
	}*/

#pragma endregion

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
			toFormation = CtoScene::GoToScene(5);
			if (toFormation == "CQuestpage")
			{
				CManager::SetSceneChangeFlag(true);
				CManager::SetScene<CQuestPage>();
			}
		}
	}

#pragma endregion
}

void CQuest::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}