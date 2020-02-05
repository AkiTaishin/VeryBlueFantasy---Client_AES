#include "scene.h"
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "characterSelectButton.h"
#include "thirdCharacter.h"
#include "DirectXTex.h"
#include "texture.h"
#include "input.h"
#include "mouse.h"
#include "polygon.h"
#include "getCharacterInfo.h"
#include "toScene.h"
#include "select.h"

//int CGetCharacterInfo::m_SaveCharacterNumber;
//int CGetCharacterInfo::m_SaveCharacterNextNumber;

void CThirdCharacter::Init(std::string fileName, float x, float y)
{
	m_ScreenImg = ASPECT;
	m_ImgW = 91.0f * m_ScreenImg;
	m_ImgH = 201.0f * m_ScreenImg;

	m_Button = new CCharacterSelectButton();
	m_Button->Init(fileName, x, y);

	m_Position = XMFLOAT3(x, y, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void CThirdCharacter::Uninit()
{
	m_Button->Uninit();
}

void CThirdCharacter::Update()
{
#pragma region �|���S�����N���b�N���ꂽ���f�o�b�O�p

	if (CInput::GetKeyTrigger(VK_LBUTTON) && !CManager::m_Mouse->m_IsSelect)
	{
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// �摜�̐؂�ւ�
			CManager::m_Mouse->m_IsSelect = true;
		}
	}

	if (CInput::GetKeyRelease(VK_LBUTTON))
	{
		CManager::m_Mouse->m_IsSelect = false;

		// �N���b�N�������ꂽ�Ƃ��Ƀ{�^���̏�Ƀ}�E�X���������ꍇ
		if (m_Position.x - m_ImgW * 0.5f < CManager::m_Mouse->m_Position.x && CManager::m_Mouse->m_Position.x < m_Position.x + m_ImgW * 0.5f && m_Position.y - m_ImgH * 0.5f < CManager::m_Mouse->m_Position.y && CManager::m_Mouse->m_Position.y < m_Position.y + m_ImgH * 0.5f)
		{
			// 3�Ԗڂ̃L�����������ꂽ���Ƃ�ۑ�
			CGetCharacterInfo::m_SaveCharacterNumber = 2;

			// �Ґ����l�܂��Ă��Ȃ�������l�߂�
			if (CGetCharacterInfo::m_SaveCharacterNextNumber < CGetCharacterInfo::m_SaveCharacterNumber)
			{
				CGetCharacterInfo::m_SaveCharacterNumber = CGetCharacterInfo::m_SaveCharacterNextNumber;
				CGetCharacterInfo::m_SaveCharacterNextNumber = CGetCharacterInfo::m_SaveCharacterNumber + 1;
			}

			// �L�����I����ʂ�
			// CFormation�������ŃT�[�o�[����󂯎��
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

void CThirdCharacter::Draw()
{
	m_Button->Draw();
}