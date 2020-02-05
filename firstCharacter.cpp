#include "scene.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "characterSelectButton.h"
#include "firstCharacter.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "polygon.h"
#include "getCharacterInfo.h"
#include "toScene.h"
#include "select.h"

int CGetCharacterInfo::m_SaveCharacterNextNumber;

void CFirstCharacter::Init(std::string fileName, float x, float y)
{
	m_ScreenImg = ASPECT;
	m_ImgW = 91.0f * m_ScreenImg;
	m_ImgH = 201.0f * m_ScreenImg;

	m_Button = new CCharacterSelectButton();
	m_Button->Init(fileName, x, y);

	m_Position = XMFLOAT3(x, y, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void CFirstCharacter::Uninit()
{
	m_Button->Uninit();
}

void CFirstCharacter::Update()
{
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
			// 先頭キャラが押されたことを保存
			CGetCharacterInfo::m_SaveCharacterNumber = 0;
			CGetCharacterInfo::m_SaveCharacterNextNumber = 1;

			// キャラ選択画面へ
			// CFormationをここでサーバーから受け取る
			std::string toFormation;
			toFormation = CtoScene::GoToScene(6);
			if (toFormation == "CSelect")
			{
				CManager::SetSceneChangeFlag(true);
				CManager::SetScene<CSelect>();
			}
		}
	}

#pragma endregion
}

void CFirstCharacter::Draw()
{
	m_Button->Draw();
}