#include "scene.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "gameObject.h"
#include "polygon.h"
#include "getCharacterInfo.h"
#include "saveFormationData.h"
#include "toScene.h"
#include "mypage.h"
#include "login.h"
#include "loginButton.h"
#include "registerNumber.h"
#include "clientInfo.h"
#include "possessionChar.h"

//std::string CLogin::m_UserID;
//int CLogin::m_RegisterNumber = 0;

void CLoginButton::Init(float x, float y)
{
	m_ImgW = 141.0f * ASPECT;
	m_ImgH = 36.0f * ASPECT;

	m_Poly = new CPolygon();

	m_Poly->Init("asset/button/ApplyButton.png", m_ImgW, m_ImgH, 1.0f);

	m_Position = XMFLOAT3(x, y, 0.0f);
	m_Poly->SetPosition(m_Position);

	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Poly->SetScale(m_Scale);
}

void CLoginButton::Uninit()
{
	m_Poly->Uninit();
}

void CLoginButton::Update()
{
#pragma region 入力

	m_Poly->SetPosition(m_Position);

#pragma endregion

#pragma region ログインIDとパスワードが入力されてボタンが押された時の処理

	if (CInput::GetKeyTrigger(VK_LBUTTON) && !CManager::m_Mouse->m_IsSelect)
	{
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// 画像の切り替え
			CManager::m_Mouse->m_IsSelect = true;
		}
	}

	// ログインIDとパスワードは空白を許さない
	if (CInput::GetKeyRelease(VK_LBUTTON) && CLogin::m_LoginID != "" && CLogin::m_Pass != "")
	{
		CManager::m_Mouse->m_IsSelect = false;

		// クリックが離されたときにボタンの上にマウスがあった場合
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
#pragma region 登録されているユーザーなのか最初にLoadしてチェックする

			// 何人のユーザーが現在登録されているのか調べる
			CLogin::m_RegisterNumber = CRegister::LoadRegisterNumber();

			// 登録されているユーザーだった場合、そのユーザーの各種情報を取得する
			CLIENT_INFO GetInfo;
			GetInfo.userID = "";
			GetInfo.loginID = CLogin::m_LoginID;
			GetInfo.passward = CLogin::m_Pass;
			GetInfo.deleteKey = -1;

			GetInfo = CClientInfo::LoadClientInfo(GetInfo);

#pragma endregion

#pragma region 登録されていなかった場合は新規ユーザーなのでユーザー登録処理をする

			// 返ってきた値が空だったら(returnされたのがenptyだった場合)
			if (GetInfo.userID.size() < 1)
			{
				// 新規ユーザー登録処理を行う
				// 新規ユーザーは所持キャラなし処理
				// formationテーブルに３レコード確保する。
				CLIENT_INFO SendData;
				SendData.loginID = CLogin::m_LoginID;
				SendData.passward = CLogin::m_Pass;
				SendData.deleteKey = 1;
				CClientInfo::SaveClientInfo(SendData);

				// ユーザーID確保
				//GetInfo = CClientInfo::LoadClientInfo();
				CLogin::m_UserID = GetInfo.userID;
			}
			else
			{
				CLogin::m_UserID = GetInfo.userID;
				// まず所持キャラクターの総数をカウントする
				CPossession::GetUserPossessionChar(CLogin::m_UserID);
				// 新規ユーザーではないので所持キャラをCPossession::m_CharIDsに保存する
				// CPossession::SendUserIDandGetCharIDs(CLogin::m_UserID);
			}

#pragma endregion

#pragma region ユーザー登録orユーザー情報取得が終了したらマイページに遷移する

			std::string toFormation;
			toFormation = CtoScene::GoToScene(4);
			if (toFormation == "CMypage")
			{
				CManager::SetSceneChangeFlag(true);
				CManager::SetScene<CMypage>();
			}

#pragma endregion
		}
	}
#pragma endregion
}

void CLoginButton::Draw()
{
	m_Poly->Draw(m_Poly->m_number);
}