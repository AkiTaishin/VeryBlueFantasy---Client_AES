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
#pragma region ����

	m_Poly->SetPosition(m_Position);

#pragma endregion

#pragma region ���O�C��ID�ƃp�X���[�h�����͂���ă{�^���������ꂽ���̏���

	if (CInput::GetKeyTrigger(VK_LBUTTON) && !CManager::m_Mouse->m_IsSelect)
	{
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// �摜�̐؂�ւ�
			CManager::m_Mouse->m_IsSelect = true;
		}
	}

	// ���O�C��ID�ƃp�X���[�h�͋󔒂������Ȃ�
	if (CInput::GetKeyRelease(VK_LBUTTON) && CLogin::m_LoginID != "" && CLogin::m_Pass != "")
	{
		CManager::m_Mouse->m_IsSelect = false;

		// �N���b�N�������ꂽ�Ƃ��Ƀ{�^���̏�Ƀ}�E�X���������ꍇ
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
#pragma region �o�^����Ă��郆�[�U�[�Ȃ̂��ŏ���Load���ă`�F�b�N����

			// ���l�̃��[�U�[�����ݓo�^����Ă���̂����ׂ�
			CLogin::m_RegisterNumber = CRegister::LoadRegisterNumber();

			// �o�^����Ă��郆�[�U�[�������ꍇ�A���̃��[�U�[�̊e������擾����
			CLIENT_INFO GetInfo;
			GetInfo.userID = "";
			GetInfo.loginID = CLogin::m_LoginID;
			GetInfo.passward = CLogin::m_Pass;
			GetInfo.deleteKey = -1;

			GetInfo = CClientInfo::LoadClientInfo(GetInfo);

#pragma endregion

#pragma region �o�^����Ă��Ȃ������ꍇ�͐V�K���[�U�[�Ȃ̂Ń��[�U�[�o�^����������

			// �Ԃ��Ă����l���󂾂�����(return���ꂽ�̂�enpty�������ꍇ)
			if (GetInfo.userID.size() < 1)
			{
				// �V�K���[�U�[�o�^�������s��
				// �V�K���[�U�[�͏����L�����Ȃ�����
				// formation�e�[�u���ɂR���R�[�h�m�ۂ���B
				CLIENT_INFO SendData;
				SendData.loginID = CLogin::m_LoginID;
				SendData.passward = CLogin::m_Pass;
				SendData.deleteKey = 1;
				CClientInfo::SaveClientInfo(SendData);

				// ���[�U�[ID�m��
				//GetInfo = CClientInfo::LoadClientInfo();
				CLogin::m_UserID = GetInfo.userID;
			}
			else
			{
				CLogin::m_UserID = GetInfo.userID;
				// �܂������L�����N�^�[�̑������J�E���g����
				CPossession::GetUserPossessionChar(CLogin::m_UserID);
				// �V�K���[�U�[�ł͂Ȃ��̂ŏ����L������CPossession::m_CharIDs�ɕۑ�����
				// CPossession::SendUserIDandGetCharIDs(CLogin::m_UserID);
			}

#pragma endregion

#pragma region ���[�U�[�o�^or���[�U�[���擾���I��������}�C�y�[�W�ɑJ�ڂ���

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