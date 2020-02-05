#include "scene.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "mouse.h"
#include "renderer.h"
#include "imgui.h"
#include "useImGui.h"
#include "polygon.h"
#include "enhancement.h"
#include "formation.h"
#include "characterDetail.h"
#include "gatya.h"
#include "mypage.h"
#include "questPage.h"
#include "login.h"

// こういう書き方をしたら他のCPPでもInitしたあとのメンバにアクセスして使えるようになる
CScene*	CManager::m_Scene;
CScene*	CManager::m_NextScene;
CMouse* CManager::m_Mouse;
CuseImGui* CManager::m_Gui;
bool CManager::m_SceneChangeFlag;

CPolygon* g_Polygon;

void CManager::Init()
{
	CRenderer::Init();
	CInput::Init();

	m_Mouse = new CMouse();
	m_Mouse->Init();

	m_Gui = new CuseImGui();
	m_Gui->Create(GetWindow(), CRenderer::GetDevice(), CRenderer::GetDeviceContext());

	//SetScene<CMypage>();
	SetScene<CLogin>();
}

void CManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	CInput::Uninit();
	CRenderer::Uninit();
}

void CManager::Update()
{
	CInput::Update();
	m_Mouse->Update();
	m_Scene->Update();
}

void CManager::Draw()
{
	CRenderer::Begin();

	m_Scene->Draw();

	CRenderer::End();
}

void CManager::ChangeScene()
{
	m_Scene->Uninit();
	delete m_Scene;
	m_Scene = m_NextScene;
	m_Scene->Init();
}

bool CManager::GetSceneChangeFlag()
{
	return m_SceneChangeFlag;
}

void CManager::SetSceneChangeFlag(bool wannaChange)
{
	m_SceneChangeFlag = wannaChange;
}