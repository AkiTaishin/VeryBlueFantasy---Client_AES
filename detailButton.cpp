#include "scene.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "detailButton.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "gameObject.h"
#include "polygon.h"
#include "getCharacterInfo.h"
#include "saveFormationData.h"
#include "toScene.h"
#include "formation.h"
#include "possessionChar.h"
#include "login.h"

int CGetCharacterInfo::m_SaveCharacterNumber;

void CDetailButton::Init(std::string fileName, float x, float y, float alpha, bool IsTrue)
{
	m_ImgW = 141.0f * ASPECT;
	m_ImgH = 36.0f * ASPECT;
	m_IsApply = IsTrue;

	m_Poly = new CPolygon();

	m_Poly->Init(fileName, m_ImgW, m_ImgH, alpha);

	m_Position = XMFLOAT3(x, y, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);

	m_GetCharData = CGetCharacterInfo::GetCharInfo();
}

void CDetailButton::Uninit()
{
	m_Poly->Uninit();
}

void CDetailButton::Update()
{
#pragma region 入力

	m_Poly->SetPosition(m_Position);

#pragma endregion

#pragma region ポリゴンがクリックされたかデバッグ用

	/// <summary>
	/// 決定ボタンを押されたときにformation画面で選択した場所にそのキャラクターを保存する。
	/// つまり、DataBaseに上書きして保存する。
	/// characterの枠はstaticで管理。
	/// formationに遷移→DataBaseから情報を読み込み→キャラ選択→情報書き換え
	/// </summary>

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
			// ApplyButtonの場合
			if (m_IsApply)
			{
				// ここで通信
				SAVE_DETAIL SendData;
				SendData.number = CGetCharacterInfo::m_SaveCharacterNumber;
				SendData.id = CGetCharacterInfo::m_SaveSelectCharacterId;
				SendData.name = m_GetCharData[SendData.id].name;
				SendData.asset = m_GetCharData[SendData.id].formation;
				SendData.attack = m_GetCharData[SendData.id].attack;
				SendData.hp = m_GetCharData[SendData.id].hp;
				SendData.element = m_GetCharData[SendData.id].element;
				SendData.userID = CLogin::m_UserID;

				CSaveFormationData::SaveFormation(SendData);

				// その後画面の遷移
				// キャラ選択画面へ
				std::string toFormation;
				toFormation = CtoScene::GoToScene(2);
				if (toFormation == "CFormation")
				{
					CManager::SetSceneChangeFlag(true);
					CManager::SetScene<CFormation>();
				}
			}
			else
			{
				// キャンセルが押されたので編成位置を1つ前に戻す
				CGetCharacterInfo::m_SaveCharacterNumber -= 1;
				CGetCharacterInfo::m_SaveCharacterNextNumber -= 1;

				// キャラ選択画面へ
				std::string toFormation;
				toFormation = CtoScene::GoToScene(2);
				if (toFormation == "CFormation")
				{
					CManager::SetSceneChangeFlag(true);
					CManager::SetScene<CFormation>();
				}
			}

		}
	}

#pragma endregion
}

void CDetailButton::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}