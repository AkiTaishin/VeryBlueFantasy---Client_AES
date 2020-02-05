#include "scene.h"
#include "manager.h"
#include "DirectXTex.h"
#include "texture.h"
#include <string>
#include "select.h"
#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "gameObject.h"
#include "selectCharPoly.h"
#include "mouse.h"
#include "input.h"
#include "getCharacterInfo.h"
#include "possessionChar.h"

void CSelect::Init()
{
	AddGameObject<CCamera>(0)->Init();
	AddGameObject<CCube>(1)->Init();
	AddGameObject<CBackSpace>(2)->Init();
	AddGameObject<CHeader>(3)->Init();
	AddGameObject<CHeaderMenu>(4)->Init();
	AddGameObject<CHeaderMypage>(5)->Init();
	AddGameObject<CSelectBG>(6)->Init();

	// �����̏����̓��O�C�����ɋL�����Ă���̂ŕK�v�Ȃ��Ȃ�
	// ���̃��[�U�[���L���������̎����Ă��邩�́ACPossession::m_PossessionNumber���Ǘ����Ă���

	// Clogin::m_UserID�������Ă�L�����N�^�[��ʐM�œǂݏo��
	m_GetCharData = CGetCharacterInfo::GetCharInfo();

	// �L�����N�^�[�I���摜�̕\���ʒu����
	for (int i = 0; i < CPossession::m_PossessionNumber; i++)
	{
		float x, y;
		x = y = 0.0f;

		switch (i)
		{
		case 0:
			x = 0.0f;
			y = 0.0f;
			break;

		case 1:
			x = 95.0f;
			y = 0.0f;
			break;

		case 2:
			x = 190.0f;
			y = 0.0f;
			break;

		case 3:
			x = 285.0f;
			y = 0.0f;
			break;

		case 4:
			x = 0.0f;
			y = 100.0f;
			break;

		case 5:
			x = 95.0f;
			y = 100.0f;
			break;

		case 6:
			x = 190.0f;
			y = 100.0f;
			break;

		case 7:
			x = 285.0f;
			y = 100.0f;
			break;
		}

		// �摜�f�[�^�A�\�����W�A�\�����W�A�L����ID
		AddGameObject<CSelectCharPoly>(7 + i)->Init(m_GetCharData[i].asset, -142.0f + x, -215.0f + y, i);
	}
}

void CSelect::Uninit()
{
	CScene::Uninit();
}

void CSelect::Update()
{
	CManager::m_Mouse->Update();
	CScene::Update();
}

void CSelect::Draw()
{
	CScene::Draw();
	DebugRender();
}

void CSelect::DebugRender()
{
	CManager::m_Gui->SetFrame();

#pragma region �}�E�X���WDebugPrint

	ImGui::Begin("MouseCondition");

	float mouse_x = CManager::m_Mouse->m_Position.x;
	float mouse_y = CManager::m_Mouse->m_Position.y;
	float mouse_z = CManager::m_Mouse->m_Position.z;
	bool mouse_flag = CManager::m_Mouse->m_IsSelect;

	ImGui::Text(std::to_string(mouse_x).c_str());
	ImGui::Text(std::to_string(mouse_y).c_str());
	ImGui::Text(std::to_string(mouse_z).c_str());
	ImGui::Text(std::to_string(mouse_flag).c_str());

	ImGui::End();

#pragma endregion

#pragma region �e��PositionDebugPrint

	ImGui::Begin("GameObjectPosition");

	DebugImGui();

	ImGui::End();

#pragma endregion

	CManager::m_Gui->Render();
}