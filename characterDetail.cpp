#include "scene.h"
#include "manager.h"
#include "DirectXTex.h"
#include "texture.h"
#include "getCharacterInfo.h"
#include <string>
#include "characterDetail.h"
#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "gameObject.h"
#include "selectCharPoly.h"
#include "detailCharPoly.h"
#include "detailPoly.h"
#include "detailButton.h"
#include "mouse.h"
#include "input.h"

void CCharacterDetail::Init()
{
	AddGameObject<CCamera>(0)->Init();
	AddGameObject<CCube>(1)->Init();
	AddGameObject<CBackSpace>(2)->Init();
	AddGameObject<CHeader>(3)->Init();
	AddGameObject<CHeaderMenu>(4)->Init();
	AddGameObject<CHeaderMypage>(5)->Init();
	AddGameObject<CDetailBG>(6)->Init();
	AddGameObject<CDetailPoly>(7)->Init("asset/formation/DetailBox2.png", 316.0f, 295.0f, 0.0f, -130.0f);

	m_GetCharData = CGetCharacterInfo::m_GetCharInfo;

	AddGameObject<CDetailCharPoly>(8)->Init(m_GetCharData[CGetCharacterInfo::m_SaveSelectCharacterId].detail);

	AddGameObject<CDetailPoly>(9)->Init("asset/formation/SSR_Ribbon.png", 316.0f, 50.0f, 0.0f, -300.0f);

	AddGameObject<CDetailButton>(10)->Init("asset/button/ApplyButton.png", 90.0f, 100.0f, 1.0f, true);
	AddGameObject<CDetailButton>(11)->Init("asset/button/CancelButton.png", -90.0f, 100.0f, 1.0f, false);

	// CGetCharacterInfo::m_SaveSelectCharacterId にあらかじめ保存してある情報をもとに
	// どのキャラクターが選択されたかを取得する。
}

void CCharacterDetail::Uninit()
{
	CScene::Uninit();
}

void CCharacterDetail::Update()
{
	CManager::m_Mouse->Update();
	CScene::Update();
}

void CCharacterDetail::Draw()
{
	CScene::Draw();
	DebugRender();
}

void CCharacterDetail::DebugRender()
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