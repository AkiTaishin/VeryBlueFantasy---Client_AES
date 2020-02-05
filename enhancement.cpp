/// <summary>
/// ïêäÌã≠âªÉyÅ[ÉW
/// </summary>
#include "scene.h"
#include "manager.h"
#include <string>
#include "enhancement.h"
#include "main.h"
#include <list>
#include <vector>
#include "renderer.h"
#include "gameObject.h"
#include "mouse.h"
#include "input.h"

void CEnhancement::Init()
{
	AddGameObject<CCamera>(0)->Init();
	AddGameObject<CCube>(1)->Init();
	AddGameObject<CBackground>(2)->Init();
	AddGameObject<CHeader>(3)->Init();
	AddGameObject<CHeaderMenu>(4)->Init();
	AddGameObject<CHeaderMypage>(5)->Init();
}

void CEnhancement::Uninit()
{
	CScene::Uninit();
}

void CEnhancement::Update()
{
	CManager::m_Mouse->Update();
	CScene::Update();
}

void CEnhancement::Draw()
{
	CScene::Draw();
}