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

	// ここの処理はログイン時に記憶しているので必要なくなる
	// そのユーザーがキャラを何体持っているかは、CPossession::m_PossessionNumberが管理している

	// Clogin::m_UserIDが持ってるキャラクターを通信で読み出す
	m_GetCharData = CGetCharacterInfo::GetCharInfo();

	// キャラクター選択画像の表示位置決定
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

		// 画像データ、表示座標、表示座標、キャラID
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