#include "scene.h"
#include "manager.h"
#include <string>
#include <list>
#include <vector>
#include "main.h"
#include "renderer.h"
#include "gameObject.h"
#include "loginButton.h"
#include "mouse.h"
#include "input.h"
#include "login.h"

std::string CLogin::m_UserID;
std::string CLogin::m_LoginID;
std::string CLogin::m_Pass;
int CLogin::m_RegisterNumber;

void CLogin::Init()
{
	AddGameObject<CCamera>(0)->Init();
	AddGameObject<CBackSpace>(2)->Init();
	AddGameObject<CHeader>(3)->Init();
	AddGameObject<CHeaderMenu>(4)->Init();
	AddGameObject<CHeaderMypage>(5)->Init();
	AddGameObject<CFormationFrame>(6)->Init();
	AddGameObject<CLoginButton>(7)->Init(0.0f, -100.0f);
}

void CLogin::Uninit()
{
	CScene::Uninit();
}

void CLogin::Update()
{
	CManager::m_Mouse->Update();
	CScene::Update();
}

void CLogin::Draw()
{
	CScene::Draw();
	DebugRender();
}

void CLogin::DebugRender()
{
	CManager::m_Gui->SetFrame();

#pragma region ユーザー登録＆認証

	/// <summary>
	/// m_LoginIDにはログインID
	/// m_Passにパスワードが保存される。
	/// 
	/// Loginシーンでボタンが押されたときにLoginIDとPassが確定され、新規登録orユーザー認証を行う。
	/// 新規登録の場合DatabaseにLoginIDとPass、一意のユーザーIDを付与する。
	/// </summary>

	ImGui::Begin("Login");

	static char buf[10] = "";
	ImGui::InputTextWithHint("LoginID", "Within 10 letters", buf, 10, ImGuiInputTextFlags_CharsNoBlank);
	m_LoginID = buf;

	static char bufpass[10] = "password"; // 最初に入力しておく文字
	// 空白を許可しない入力欄にするには ImGuiInputTextFlags_CharsNoBlank を使います。
	ImGui::InputText("Password", bufpass, 10, ImGuiInputTextFlags_CharsNoBlank);
	m_Pass = bufpass;

	ImGui::End();

#pragma endregion

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