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

#pragma region ���[�U�[�o�^���F��

	/// <summary>
	/// m_LoginID�ɂ̓��O�C��ID
	/// m_Pass�Ƀp�X���[�h���ۑ������B
	/// 
	/// Login�V�[���Ń{�^���������ꂽ�Ƃ���LoginID��Pass���m�肳��A�V�K�o�^or���[�U�[�F�؂��s���B
	/// �V�K�o�^�̏ꍇDatabase��LoginID��Pass�A��ӂ̃��[�U�[ID��t�^����B
	/// </summary>

	ImGui::Begin("Login");

	static char buf[10] = "";
	ImGui::InputTextWithHint("LoginID", "Within 10 letters", buf, 10, ImGuiInputTextFlags_CharsNoBlank);
	m_LoginID = buf;

	static char bufpass[10] = "password"; // �ŏ��ɓ��͂��Ă�������
	// �󔒂������Ȃ����͗��ɂ���ɂ� ImGuiInputTextFlags_CharsNoBlank ���g���܂��B
	ImGui::InputText("Password", bufpass, 10, ImGuiInputTextFlags_CharsNoBlank);
	m_Pass = bufpass;

	ImGui::End();

#pragma endregion

//#pragma region �}�E�X���WDebugPrint
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
//#pragma region �e��PositionDebugPrint
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