#include <string>
#include "mypage.h"
#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "gameObject.h"
#include "mouse.h"
#include "scene.h"
#include "manager.h"
#include "input.h"

//CuseImGui* CManager::m_Gui;
//CMouse* CManager::m_Mouse;
//

void CMypage::Init()
{
	AddGameObject<CCamera>(0)->Init();
	AddGameObject<CCube>(1)->Init();
	AddGameObject<CBackground>(2)->Init();
	AddGameObject<CCharacterPoly>(3)->Init();
	AddGameObject<CHeader>(4)->Init();
	AddGameObject<CHeaderMenu>(5)->Init();
	AddGameObject<CHeaderTop>(6)->Init();
	AddGameObject<CMenuBG>(7)->Init();
	AddGameObject<CQuest>(8)->Init();
	AddGameObject<CParty>(9)->Init();
	AddGameObject<CSlot>(10)->Init();
	AddGameObject<CWeapon>(11)->Init();
	AddGameObject<CHeaderPower>(12)->Init();
	AddGameObject<CHeaderSound>(13)->Init();
	AddGameObject<CHeaderTown>(14)->Init();
}

void CMypage::Uninit()
{
	CScene::Uninit();
}

void CMypage::Update()
{
	//CManager::m_Mouse->Update();
	CScene::Update();
}

void CMypage::Draw()
{
	CScene::Draw();
	DebugRender();
}

void CMypage::DebugRender()
{
	CManager::m_Gui->SetFrame();

#pragma region マウス座標DebugPrint

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

#pragma region 各種PositionDebugPrint

	ImGui::Begin("GameObjectPosition");

	DebugImGui();

	ImGui::End();

#pragma endregion

	CManager::m_Gui->Render();
}