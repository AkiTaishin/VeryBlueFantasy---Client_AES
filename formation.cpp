#include "scene.h"
#include "manager.h"
#include <string>
#include <list>
#include <vector>
#include "formation.h"
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "mouse.h"
#include "input.h"
#include "getFormationData.h"

#define DETAIL_ENPTY	(-1)

void CFormation::Init()
{
	m_GetFormation = CGetFormationData::GetFormationData();

	AddGameObject<CCamera>(0)->Init();
	AddGameObject<CCube>(1)->Init();
	AddGameObject<CBackSpace>(2)->Init();
	AddGameObject<CHeader>(3)->Init();
	AddGameObject<CHeaderMenu>(4)->Init();
	AddGameObject<CHeaderMypage>(5)->Init();
	AddGameObject<CFormationFrame>(6)->Init();
	AddGameObject<CFormationGuran>(7)->Init();
	AddGameObject<CCharButton>(8)->Init(-140.0f, -80.0f, 0.0f, 2, true);
	AddGameObject<CWeaponButton>(9)->Init(0.0f, -80.0f, 0.0f, 1, true);
	AddGameObject<CSummonButton>(10)->Init(140.0f, -80.0f, 0.0f, 1, true);
	AddGameObject<CCharButton>(11)->Init(-140.0f, -80.0f, 0.0f, 1, false);
	AddGameObject<CWeaponButton>(12)->Init(0.0f, -80.0f, 0.0f, 2, false);
	AddGameObject<CSummonButton>(13)->Init(140.0f, -80.0f, 0.0f, 2, false);
	AddGameObject<CMainMenberPoly>(14)->Init();
	AddGameObject<CTemplateCharacter>(15)->Init("asset/formation/template.png", -133.0f, 180.0f);
	AddGameObject<CTemplateCharacter>(16)->Init("asset/formation/template.png", 0.0f, 180.0f);
	AddGameObject<CTemplateCharacter>(17)->Init("asset/formation/template.png", 133.0f, 180.0f);

#pragma region キャラクター情報の読み出し

	if (m_GetFormation.size() > 0)
	{
		if (m_GetFormation[0].data.id > DETAIL_ENPTY)
		{
			AddGameObject<CFirstCharacter>(18)->Init(m_GetFormation[0].data.asset, -133.0f, 115.0f);
		}
		else
		{
			AddGameObject<CFirstCharacter>(18)->Init("asset/formation/characterSelectButton.png", -133.0f, 115.0f);
		}

		if (m_GetFormation[1].data.id > DETAIL_ENPTY)
		{
			AddGameObject<CSecondCharacter>(19)->Init(m_GetFormation[1].data.asset, 0.0f, 115.0f);
		}
		else
		{
			AddGameObject<CSecondCharacter>(19)->Init("asset/formation/characterSelectButton.png", 0.0f, 115.0f);
		}

		if (m_GetFormation[2].data.id > DETAIL_ENPTY)
		{
			AddGameObject<CThirdCharacter>(20)->Init(m_GetFormation[2].data.asset, 133.0f, 115.0f);
		}
		else
		{
			AddGameObject<CThirdCharacter>(20)->Init("asset/formation/characterSelectButton.png", 133.0f, 115.0f);
		}
	}
	else
	{
		AddGameObject<CFirstCharacter>(18)->Init("asset/formation/characterSelectButton.png", -133.0f, 115.0f);
		AddGameObject<CSecondCharacter>(19)->Init("asset/formation/characterSelectButton.png", 0.0f, 115.0f);
		AddGameObject<CThirdCharacter>(20)->Init("asset/formation/characterSelectButton.png", 133.0f, 115.0f);
	}

#pragma endregion
}

void CFormation::Uninit()
{
	CScene::Uninit();
}

void CFormation::Update()
{
	CManager::m_Mouse->Update();
	CScene::Update();
}

void CFormation::Draw()
{
	CScene::Draw();
	DebugRender();
}

void CFormation::DebugRender()
{
	CManager::m_Gui->SetFrame();

//#pragma region マウス座標DebugPrint
//
//	ImGui::Begin("MouseCondition");
//
//	float mouse_x = CManager::m_Mouse->m_Position.x;
//	float mouse_y = CManager::m_Mouse->m_Position.y;
//	float mouse_z = CManager::m_Mouse->m_Position.z;
//	bool mouse_flag = CManager::m_Mouse->m_IsSelect;
//
//	ImGui::Text(std::to_string(mouse_x).c_str());
//	ImGui::Text(std::to_string(mouse_y).c_str());
//	ImGui::Text(std::to_string(mouse_z).c_str());
//	ImGui::Text(std::to_string(mouse_flag).c_str());
//
//	ImGui::End();
//
//#pragma endregion
//
//#pragma region 各種PositionDebugPrint
//
//	ImGui::Begin("GameObjectPosition");
//
//	DebugImGui();
//
//	ImGui::End();
//
//#pragma endregion

	CManager::m_Gui->Render();
}