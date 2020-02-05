#include "scene.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "getCharacterInfo.h"
#include "gameObject.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "polygon.h"
#include "selectCharPoly.h"
#include "toScene.h"
#include "characterDetail.h"

int CGetCharacterInfo::m_SaveSelectCharacterId;

void CSelectCharPoly::Init(std::string fileName, float x, float y, int id)
{
	m_ImgW = 70.0f * ASPECT;
	m_ImgH = 40.0f * ASPECT;

	m_Poly = new CPolygon();
	m_Poly->Init(fileName, m_ImgW, m_ImgH, 1.0);
	m_Poly->m_number = 1;

	m_Position = XMFLOAT3(x, y, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);

	m_CharacterID = id;
}

void CSelectCharPoly::Uninit()
{
	m_Poly->Uninit();
}

void CSelectCharPoly::Update()
{
	m_Poly->SetPosition(m_Position);

#pragma region ポリゴンがクリックされたかデバッグ用

	if (CInput::GetKeyTrigger(VK_LBUTTON) && !CManager::m_Mouse->m_IsSelect)
	{
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// 画像の切り替え
			CManager::m_Mouse->m_IsSelect = true;
		}
	}

	if (CInput::GetKeyRelease(VK_LBUTTON))
	{
		CManager::m_Mouse->m_IsSelect = false;

		// クリックが離されたときにボタンの上にマウスがあった場合
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// キャラ選択画面へ
			// CFormationをここでサーバーから受け取る
			std::string toFormation;
			toFormation = CtoScene::GoToScene(0);
			if (toFormation == "CCharcterDetail")
			{
				CGetCharacterInfo::m_SaveSelectCharacterId = m_CharacterID;
				CManager::SetSceneChangeFlag(true);
				CManager::SetScene<CCharacterDetail>();
			}
		}
	}

#pragma endregion
}

void CSelectCharPoly::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}